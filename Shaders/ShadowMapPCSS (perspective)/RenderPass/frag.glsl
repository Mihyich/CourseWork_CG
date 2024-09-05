#version 460 core

// Точечный источник света
struct PointLight
{
    vec3 position;   // Позиция
    float radius;    // Радиус действия
    vec3 color;      // Цвет
    float intensity; // Интенсивность
};

// Прожекторный источник света
struct SpotLight
{
    vec3 position;     // Позиция
    vec3 direction;    // Направление
    float innerCutoff; // Угол (в радианах) внутреннего конуса
    float outerCutoff; // Угол (в радианах) внешнего конуса
    float radius;      // Радиус действия
    vec3 color;        // Цвет
    float intensity;   // Интенсивность
};

// Универсальный источник света
struct Light
{
    vec3 position;     // Позиция
    vec3 direction;    // Направление
    vec3 color;        // Цвет
    vec2 option;       // Радиус действия и Интенсивность
    vec2 cutoff;       // Внутренний и внешний углы в радианах
    int type;          // Тип источника света: 0 - PointLight; 1
};

layout(std140, binding = 0) uniform Lighting
{
    // Входной буфер, описывающий источник света
    Light light;
};

out vec4 FragColor;

in vec4 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform float shadowBias = 0.001;
uniform float pcfRadius = 1.0;

#define PI 3.14159265358

vec3 computePointLightColor(vec3 fragPos, vec3 normal, PointLight light)
{
    // Вектор от фрагмента до источника света
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Расстояние до источника света
    float distance = length(light.position - fragPos);
    
    // Интенсивность света с учетом расстояния (уменьшение света по квадрату расстояния)
    float attenuation = max(1.0 - (distance / light.radius), 0.0);
    
    // Расчет диффузного освещения
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Цвет освещения
    vec3 lightColor = light.color * light.intensity * attenuation;
    
    return lightColor * diff;
}

vec3 computeSpotLightColor(vec3 fragPos, vec3 normal, SpotLight light)
{
    // Вектор от фрагмента до источника света
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Расстояние до источника света
    float distance = length(light.position - fragPos);
    
    // Интенсивность света с учетом расстояния (уменьшение света по квадрату расстояния)
    float attenuation = max(1.0 - (distance / light.radius), 0.0);
    
    // Расчет диффузного освещения
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Угол между направлением источника света и направлением к источнику света
    float spotEffect = dot(normalize(light.direction), -lightDir);
    
    // Проверка попадания в конус
    float theta = cos(light.innerCutoff);
    float phi = cos(light.outerCutoff);
    float epsilon = theta - phi;
    float intensity = clamp((spotEffect - phi) / epsilon, 0.0, 1.0);
    
    // Цвет освещения
    vec3 lightColor = light.color * light.intensity * attenuation * intensity;
    
    return lightColor * diff;
}

vec3 computeLightColor(vec3 fragPos, vec3 normal)
{
    PointLight pl;
    SpotLight sl;
    vec3 diff;

    if (light.type == 0)
    {
        pl.position = light.position;
        pl.radius = light.option.x;
        pl.color = light.color;
        pl.intensity =  light.option.y;

        diff = computePointLightColor(fragPos, normal, pl);
    }
    else
    {
        sl.position = light.position;
        sl.direction = light.direction;
        sl.innerCutoff = light.cutoff.x;
        sl.outerCutoff = light.cutoff.y;
        sl.radius = light.option.x;
        sl.color = light.color;
        sl.intensity = light.option.y;

        diff = computeSpotLightColor(fragPos, normal, sl);
    }

    return diff;
}

vec2 sampleDisk(int sampleIndex, int numSamples)
{
    float angle = float(sampleIndex) / float(numSamples) * 2.0 * PI;
    float radius = sqrt(float(sampleIndex) / float(numSamples));
    return vec2(cos(angle), sin(angle)) * radius;
}

float SearchBlocker(vec3 projCoords, float searchRadius)
{
    int numSamples = 16;  // количество выборок вокруг текущего фрагмента
    float blockerDepthSum = 0.0;
    int numBlockers = 0;

    // Выполняем выборки вокруг текущей точки (в пределах searchRadius)
    for (int i = 0; i < numSamples; ++i) {
        // Генерация смещенной позиции выборки (например, случайное смещение или с использованием диска)
        vec2 offset = sampleDisk(i, numSamples) * searchRadius;

        // Прочитаем глубину из карты теней для соседней точки
        float depthInShadowMap = texture(shadowMap, projCoords.xy + offset).r;

        // Если точка блокирует свет, добавляем её глубину
        if (depthInShadowMap < projCoords.z) {
            blockerDepthSum += depthInShadowMap;
            numBlockers++;
        }
    }

    // Если найдены блокирующие объекты, усредняем их глубину
    if (numBlockers > 0)
    {
        return blockerDepthSum / numBlockers;
    }

    // Если блокирующие объекты не найдены, возвращаем -1
    return -1.0;
}

float EstimatePenumbraSize(float fragDepth, float blockerDepth)
{
    // Если нет блокирующего объекта, полутени нет
    if (blockerDepth < 0.0)
    {
        return 0.0;
    }

    // Радиус источника света (например, диска для направленного света)
    float lightRadius = 0.05;  // Настраиваемая величина, зависит от источника света

    // Оценка размера полутени
    float penumbraSize = (fragDepth - blockerDepth) / blockerDepth * lightRadius;

    // Возвращаем оценку размера полутени
    return penumbraSize;
}

float PerformPCF(vec3 projCoords, float penumbraSize)
{
    // Определение ядра для PCF
    int sampleCount = 16;  // Количество выборок (можно регулировать для улучшения качества)
    float shadow = 0.0;
    
    // Применяем значение penumbraSize для масштабирования области выборки
    float filterRadius = penumbraSize;

    // Цикл по выборкам вокруг текущей координаты в пространстве света
    for (int x = -sampleCount / 2; x < sampleCount / 2; ++x)
    {
        for (int y = -sampleCount / 2; y < sampleCount / 2; ++y)
        {
            // Смещаем координаты для выборок в окрестности
            vec2 offset = vec2(float(x), float(y)) * filterRadius / float(sampleCount);
            vec2 sampleCoords = projCoords.xy + offset;

            // Проверка, чтобы выборки не выходили за границы текстуры
            if (sampleCoords.x >= 0.0 && sampleCoords.x <= 1.0 && sampleCoords.y >= 0.0 && sampleCoords.y <= 1.0)
            {
                // Получаем глубину из карты теней
                float closestDepth = texture(shadowMap, sampleCoords).r;

                // Текущая глубина фрагмента
                float currentDepth = projCoords.z;

                // Проверка тени для этой выборки
                if (closestDepth < currentDepth)
                {
                    shadow += 1.0;
                }
            }
        }
    }

    // Усредняем результат выборок
    shadow /= float(sampleCount * sampleCount);

    return shadow;
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Преобразуем координаты в проекционные
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords.xy = projCoords.xy * 0.5 + 0.5;

    // Шаг 1: Оценка блокирующих объектов
    float blockerDepth = SearchBlocker(projCoords, 0.02);

    if (blockerDepth < 0.0)
    {
        return 1.0; // Освещённый фрагмент
    }

    // Шаг 2: Оценка размера полутени
    float penumbraSize = EstimatePenumbraSize(projCoords.z, blockerDepth);

    // Шаг 3: Применение PCF с изменяемым радиусом
    return PerformPCF(projCoords, penumbraSize);
}

void main()
{
    vec3 color = vec3(0.5);
    vec3 ambient = 0.15 * color;

    vec3 diffuse = computeLightColor(FragPos.xyz, Normal) * color;

    float shadow = ShadowCalculation(FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * diffuse);

    FragColor = vec4(lighting, 1.0);
}