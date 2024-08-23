// Алгоритм и пояснения в конце файла

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

// Вершинные данные
struct RayTraceVertex
{
    // Позиция:
    float px;
    float py;
    float pz;
    // Нормаль:
    float nx;
    float ny;
    float nz;
}; // float - универсальное выравнивание, оно совпадает со своим размером и ничего не нужно конвертировать

// Вершинные данные треугольника для использования в шейдере
struct RayTraceVertexTriangle
{
    RayTraceVertex v1; // Вершина 1
    RayTraceVertex v2; // Вершина 2
    RayTraceVertex v3; // Вершина 3
};

// Ограничивающая сфера
struct RayTraceBS
{
    // центер:
    float cx;
    float cy;
    float cz;
    // радиус:
    float r;
}; // float - универсальное выравнивание...

// Индексы дочерних узлов дерева в массиве
struct RayTraceChildIndex
{
    int left;  // Индекс левого дочернего узла в массиве
    int right; // Индекс правого дочернего узла в массиве
};

// Индексы треугольников и матриц в отдельных массивах
struct RayTraceDataIndex
{
    int triangle; // Индекс треугольника (или -1, если это не лист)
    int matrix;   // Индекс матрицы (-1, если узел не относится к мешу)
};

// Bounding Volume Hierarchy
struct RayTraceBVHNode
{
    RayTraceBS BS;         // Ограничиавющая сфера
    RayTraceChildIndex CI; // Дочерние индексы
    RayTraceDataIndex DI;  // Индексы данных
    int parent;            // Индекс родительского узла (-1 если нет)
};

layout(std140, binding = 0) uniform Lighting
{
    // Входной буфер, описывающий источник света
    Light light;
};

layout(std430, binding = 1) buffer Triangles
{
    // Входной буфер, хранящий вершинные данные всей сцены
    RayTraceVertexTriangle triangles[];
};

layout(std430, binding = 2) buffer Matrices
{
    // Входной буфер, хранящий матрицы модели для каждого объекта в сцене
    mat4 matrices[];
};

layout(std430, binding = 3) buffer Bvh
{
    // Входной буфер, хранящий дерево BVH
    RayTraceBVHNode bvh[];
};

layout (local_size_x = 16, local_size_y = 16) in;

uniform vec3 viewPos;
uniform mat4 view;
uniform mat4 projection;

#define EPSILON 0.0001
#define FLT_MAX 3.402823466e+38

// Выходное изображение
layout(rgba32f, binding = 4) uniform image2D colorImage;

// Луч
struct Ray
{
    vec3 origin; // Начало луча
    vec3 dir;    // Направление луча
};

// Треугольник
struct Triangle
{
    vec3 v1; // 1 позиция вершины
    vec3 v2; // 2 позиция вершины
    vec3 v3; // 3 позиция вершины
};

// Вычисление цвета света от точечного источника света
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

// Вычисление цвета света от прожектороного источника света
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

// Лаунчер вычисления цвета света от источника света
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

// Вычисление барицентрических координат
vec3 computeBarycentricCoordinates(vec3 P, vec3 A, vec3 B, vec3 C)
{
    vec3 v0 = B - A;
    vec3 v1 = C - A;
    vec3 v2 = P - A;

    float d00 = dot(v0, v0);
    float d01 = dot(v0, v1);
    float d11 = dot(v1, v1);
    float d20 = dot(v2, v0);
    float d21 = dot(v2, v1);

    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0 - v - w;

    return vec3(u, v, w);
}

// Интерполяция векторов
vec3 interpolateVector(vec3 barycentricCoords, vec3 A, vec3 B, vec3 C)
{
    // сдается мне что, это банальное умножение матрицы на вектор
    return barycentricCoords.x * A + barycentricCoords.y * B + barycentricCoords.z * C;
}

// Трассировка сферы
// Положительный результат даже если луч находится внутри сферы
bool traceRayBoundingSphere(RayTraceBS RTBS, Ray ray)
{
    vec3 oc = ray.origin - vec3(RTBS.cx, RTBS.cy, RTBS.cz);

    float a = dot(ray.dir, ray.dir);
    float b = 2.0 * dot(oc, ray.dir);
    float c = dot(oc, oc) - RTBS.r * RTBS.r;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0)
    {
        return false;
    }
    
    float sqrtDisc = sqrt(discriminant);
    float t1 = (-b - sqrtDisc) / (2.0 * a);
    float t2 = (-b + sqrtDisc) / (2.0 * a);
    
    return t1 > 0.0 || t2 > 0.0;
}

// Трассировка треугольника (Möller–Trumbore)
// обещает обрабатывать как CWW треугольники, так и CW
bool traceRayTriangle(Triangle triangle, Ray ray, out float t)
{
    vec3 edge1 = triangle.v2 - triangle.v1;
    vec3 edge2 = triangle.v3 - triangle.v1;
    vec3 normal = cross(edge1, edge2);
    vec3 h = cross(ray.dir, edge2);

    if (dot(normal, ray.dir) < 0.0)
        return false;

    float a = dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false;
    
    float f = 1.0 / a;
    vec3 s = ray.origin - triangle.v1;
    float u = f * dot(s, h);

    if (u < 0.0 || u > 1.0)
        return false;

    vec3 q = cross(s, edge1);
    float v = f * dot(ray.dir, q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    t = f * dot(edge2, q);

    return t > EPSILON;
}

// Поиск следующего индекса узла, идущего сразу
// после поддерева узла по индексу index
// в положительном направлении
int skipSubTree(int index)
{
    while (bvh[index].CI.right > -1 || bvh[index].CI.left > -1)
    {
        index = bvh[index].CI.right > -1 ? bvh[index].CI.right : bvh[index].CI.left;
    }

    ++index;

    return index;
}

// Обхода BVH дерева
vec4 traceRayBVH(Ray ray)
{
    RayTraceBVHNode node; // Текущий узел BVH
    RayTraceBS TRBS; // Текущий огриничивающий объем (сфера)
    RayTraceVertexTriangle triangle; // Текущий треугольник c вершинными данными
    Triangle trig; // Треугольник для трассировки
    mat4 model; // Текущая матрица модели
    mat3 normModel; // Нормальная матрица модели
    int curIndex = 0; // Корневой узел в массиве ВСЕГДА лежит в самом начале
    int bvhLenght = bvh.length(); // Количество узлов дерева BVH

    int matrixIndex; // индекс матрицы
    int triangleIndex; // индекс треугольника

    vec4 tmpPos1; //
    vec4 tmpPos2; // Кешированные позиции
    vec4 tmpPos3; //

    vec3 tmpNorm1; //
    vec3 tmpNorm2; // Кешированные нормали
    vec3 tmpNorm3; //

    vec3 FragPos; // Позиция фрагмента
    vec3 FragNorm; // Нормаль фрагмента
    vec3 barycentricCoords; // барицентрические, вспомогательные координаты

    float t; // Расстояние до тругольника
    float closestT = FLT_MAX; // Ближайшее расстояние до треугольника
    int closestTriangleIndex; // Индекс ближайшего треугольника
    int closestMatrixIndex; // Индекс ближайшей матрица для этого треугольника

    vec4 color = vec4(0.0, 0.0, 0.0, 1.0); // Нет света

    while (curIndex > -1 && curIndex < bvhLenght)
    {
        // Получить текущий узел
        node = bvh[curIndex];

        matrixIndex = node.DI.matrix;
        triangleIndex = node.DI.triangle;

        // Если узел не связующий (нет матрицы)
        if (matrixIndex < 0)
        {
            // Все первые 3 под-пункта выполнены
            ++curIndex; // Вжух... (づ￣ 3￣)づ (Продолжить ПРЕФИКСНЫЙ обход дерева)
        }
        // Если узел связующий (есть матрица, но нет треугольника)
        else if (triangleIndex < 0)
        {
            // Подготовка данных
            model = matrices[matrixIndex]; // Матрицы модели
            TRBS.r = node.BS.r; // радиус ограничивающей сферы

            // Учет локальности данных* (перевод в мировые)
            tmpPos1 = model * vec4(node.BS.cx, node.BS.cy, node.BS.cz, 1.0);
            TRBS.cx = tmpPos1.x;
            TRBS.cy = tmpPos1.y;
            TRBS.cz = tmpPos1.z;

            // Трассировка
            if (traceRayBoundingSphere(TRBS, ray))
            {
                // Попал!

                // Все 3 под-пункта пункта 2 выполнены (погружение в дерево)
                ++curIndex; // Вжух... (づ￣ 3￣)づ
            }
            else
            {
                // Мимо!

                // Оптимизицонный подбор индекса следующего узла
                curIndex = skipSubTree(curIndex);
            }
        }
        // Если узел - лист (есть матрица и треугольник)
        else
        {
            // Подготовка данных
            model = matrices[matrixIndex]; // Матрицы модели
            TRBS.r = node.BS.r; // радиус ограничивающей сферы

            // Учет локальности данных* (перевод в мировые)
            tmpPos1 = model * vec4(node.BS.cx, node.BS.cy, node.BS.cz, 1.0);
            TRBS.cx = tmpPos1.x;
            TRBS.cy = tmpPos1.y;
            TRBS.cz = tmpPos1.z;

            // То же и для треугольника (пока только позиции)
            trig.v1 = vec3(model * vec4(triangles[triangleIndex].v1.px, triangles[triangleIndex].v1.py, triangles[triangleIndex].v1.pz, 1.0));
            trig.v2 = vec3(model * vec4(triangles[triangleIndex].v2.px, triangles[triangleIndex].v2.py, triangles[triangleIndex].v2.pz, 1.0));
            trig.v3 = vec3(model * vec4(triangles[triangleIndex].v3.px, triangles[triangleIndex].v3.py, triangles[triangleIndex].v3.pz, 1.0));

            if (traceRayTriangle(trig, ray, t))
            {
                // Попал!
                
                // Тест глубины (запомнить ближайшее расстояние)
                if (t < closestT)
                {
                    closestTriangleIndex = triangleIndex;
                    closestMatrixIndex = matrixIndex;
                    closestT = t;
                }

                // Переход к следующему узлу
                ++curIndex;
            }
            else
            {
                // Мимо!

                // Оптимизационный подбор индекса следующего узла
                curIndex = skipSubTree(curIndex);
            }
        }
    }

    // Если ближайшее расстояние изменилось, значит было столкновение с треугольником
    // Следовательно, нужно рассчитать освещение
    if (closestT < FLT_MAX)
    {
        // Подготовить нормали

        // Поизиция фрагмента
        FragPos = ray.origin + closesT * ray.dir;

        // Нормальная матрица
        normModel = transpose(inverse(mat3(model)));

        // Перевод нормалей в мировое пространство
        tmpNorm1 = normModel * vec3(triangles[triangleIndex].v1.nx, triangles[triangleIndex].v1.ny, triangles[triangleIndex].v1.nz);
        tmpNorm2 = normModel * vec3(triangles[triangleIndex].v2.nx, triangles[triangleIndex].v2.ny, triangles[triangleIndex].v2.nz);
        tmpNorm3 = normModel * vec3(triangles[triangleIndex].v3.nx, triangles[triangleIndex].v3.ny, triangles[triangleIndex].v3.nz);

        // Барицентрические координаты
        barycentricCoords = computeBarycentricCoordinates(FragPos, tmpNorm1, tmpNorm2, tmpNorm3);

        // Интерполированная нормаль
        FragNorm = interpolateVector(barycentricCoords, tmpNorm1, tmpNorm2, tmpNorm3);

        // Вычисление освещения
        color = vec4(computeLightColor(FragPos, FragNorm), 1.0);
    }

    return color;
}

void main()
{
    Ray ray; // Я, лучик...
    vec4 color; // Цвет света

    // Координаты пикселя (x, y) на экране
    ivec2 pixelCoord = ivec2(gl_GlobalInvocationID.xy);

    // Размеры изображения
    ivec2 imageSize = imageSize(colorImage);

    // Нормализация координат пикселя в диапазон [0, 1]
    vec2 uv = vec2(pixelCoord) / vec2(imageSize);

    // Конвертация UV в NDC: [-1, 1]
    vec2 screenSpace = uv * 2.0 - 1.0;

    // Перенос NDC в мировые координаты
    vec4 rayOrigin4D = inverse(projection * view) * vec4(screenSpace, -1.0, 1.0);

    // Учет перспективного деления, и мы имеем координату с экрана в мировом пространстве сцены
    ray.origin = rayOrigin4D.xyz / rayOrigin4D.w;

    // позиция камеры ВСЕГДА чуть ближе, чем проекционная плоскость усеченной пирамиды
    ray.dir = normalize(ray.origin - viewPos);

    // Запуск обхода BVH дерева
    color = traceRayBVH(ray);

    // Запись результата
    imageStore(colorImage, pixelCoord, color);
}

/*
===========================================================================================================
| Правила обхода дерева BVH:                                                                              |
===========================================================================================================

1. Если нет матрицы => нет ограничивающего объема => нечего трассировать

    1.1 Попытаться перейти в левый узел (должно получиться, иначе дерево структурировано с ошибками)

    1.2 Иначе в правый (хотя это не должно быть никогда)

    1.3 Иначе найти следующий узел при ПРЕФИКСНОМ обходе дерева (хотя и этого тоже не должно быть никогда)

2. Если есть матрица, но нет треугольника => есть ограничивающий объем => трассировка объема

    2.1 Попал:

        2.1.1 Попытаться перейти в левый узел (должно получиться, иначе дерево структурировано с ошибками)

        2.1.2 Иначе в правый (хотя это не должно быть никогда)

        2.1.3 Иначе найти следующий узел при ПРЕФИКСНОМ обходе дерева (хотя и этого тоже не должно быть никогда)

    2.2 Мимо: Вызвать процедуру поиска нового узла*

3. Если есть матрица и треугольник => в жопу ограничивающий объем => трассировка треугольника

    3.1 Попал: рассчитать освещение; Вызвать процедуру подъема по дереву

    3.2 Мимо: Вызвать процедуру подъема по дереву

===========================================================================================================
| Процедура переключения на следующий узел в BVH дереве:                                                  |
===========================================================================================================

BVH дерево строится ПРЕФИКСНО, соответственно его узлы и в массиве будут лежать в таком порядке,
в котором бы оно перебиралось ПРЕФИКСНО, использовав дочерние индексы.

Это прекрасно-удивительно-неожиданная информация дает выполнить переход к следующему узлу
с помощью всего лишь одной команды... += 1.

И соответсвенно, именно поэтому, корень дерева располагается в начале массива, а последний узел - в конце.

( ͠° ͟ʖ ͡°)

Что вообще касается операции "curIndex += 1":

Как уже говорилось, BVH расположено ПРЕФИКСНО по массиву, значит любое инкрементирование, равнозначно
продолжению ПРЕФИКСНОГО обхода BVH дерева.

И поэтому выполнение этого действия одним разом покрывает все 3 пункта: 1.1, 1.2 и 1.3

===========================================================================================================
| Процедура поиска нового узла*                                                                           |
===========================================================================================================

Чего нужно добиться? Нашелся СВЯЗЫВАЮЩИЙ узел, который провалил трассировку ограничивающего объема. 
Значит, все его дочерние узлы можно не проверять, так как они в нем и содержатся.

Вопрос в том, как, зная что ниже текущего узла идти бессмысленно, найти новый узел для проверки,
причем таким образом, чтобы выполнялись следующие условия:

1. Узел должен иметь минимально возможный индекс относительно массива bvh

2. Из узла невозможно добраться до исследуемого (тот с которого начался поиск) с помощью

ПРЕФИКСНОГО обхода с положительным шагом

3. Узел не может быть дочерним по отношению к исследоваемому (тот с которого начался поиск)

Иными словами, нужно найти минимальный индекс бОльший исследуемого, да еще и проверить,
чтобы это не потомок исследуемого.

Решение 1: (итеративный метод)

1. Найти самый крайний приоритетно правый узел. Это будет треугольник (так задумывалось дерево)

2. К найденному индексу прибавить 1. Та-да, либо нашлась новая ветка, либо мы достигли лимит индексов

Учитывая ПРЕФИКСНО-обходную способность дерева, индекс узла на массиве предшевствующий требуемому узлу,
будет лежать в самом низу, начиная от текущего узла, как можно правее. Навсякий случай, лучше
предположить, что в дереве может быть ошибка и учесть возможномть несуществования правого узла, только
левого. В таком случае нужно перейти в него и продолжить искать правый, пока не получится найти лист.
Как только он найден, искомый индекс = найденный + 1.

Решение 2: (ПИЗДЕЦ метод, ноооо вкусный) Пока не поддерживается

Так как, по итогу BVH - это БДДП (сука почти), если оставшееся дерево, начиная с исследуемого узла является
сбалансированным, то новый индекс высчитывается как 2 * right - lelt. Но к сожалению, это работает
не всегда. Скорее всего из-за не точностей при распределении треугольников...

Пока мысли только о том, что можно дополнить узлы информацией о том, является ли их
поддерево сбалансированным?..

Либо исправлять алгоритм построения дерева?..

Либо использовать вообще другой?..

Поэтому пока что реализация первого метода

===========================================================================================================
| Учет локальности данных*                                                                                |
===========================================================================================================

Чтобы при перестройке дерева BVH, не приходилось обновлять каждый треугольник заново,
используется массив матриц, к которым каждый узел имеет, ну или не имеет (не связующий), доступ по индексу.

В итоге, все данные изначально лежат без преобразований. Поэтому важно учитывать влияние матриц
как на треугольники, так и на ограничивающие объемы, которые в свою очередь, были вычислены на тех же
локальных данных.

*/