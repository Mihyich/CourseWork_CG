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

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Конвертация из [-1, 1] в [0, 1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Проверка на тень
    if (projCoords.z > 1.0)
        return 0.0;
    
    // Тень с использованием PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize * pcfRadius).r;
            shadow += projCoords.z - shadowBias > pcfDepth ? 1.0 : 0.0;
        }
    }

    return shadow / 9.0;
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