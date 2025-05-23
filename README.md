# CourseWork_CG

![alt text](https://github.com/Mihyich/CourseWork_CG/blob/develop/Presentation/Skull1.jpg)
![alt text](https://github.com/Mihyich/CourseWork_CG/blob/develop/Presentation/Skull2.jfif)
![alt text](https://github.com/Mihyich/CourseWork_CG/blob/develop/Presentation/Monkeys.jfif)
![alt text](https://github.com/Mihyich/CourseWork_CG/blob/develop/Presentation/GoldMonkey.png)
![alt text](https://github.com/Mihyich/CourseWork_CG/blob/develop/Presentation/Rabbit.jpg)

1. Shadow Mapping (Теневые карты)

+ Basic Shadow Mapping: Использует глубинную карту для определения теней. На первом проходе сцена рендерится с точки зрения источника света, чтобы создать глубинную карту, на втором проходе – с точки зрения камеры.
  
+ Percentage Closer Filtering (PCF): Усовершенствование базового алгоритма для сглаживания теней путем взятия нескольких выборок из теневой карты и усреднения результатов.

+ Variance Shadow Maps (VSM): Использует моменты вместо глубины для уменьшения эффекта aliasing и получения мягких теней.

+ Exponential Shadow Maps (ESM): Использует экспоненциальные значения глубины для сглаживания теней.

2. Shadow Volumes (Объемы теней)
   
+ Basic Shadow Volumes: Использует геометрию сцены для создания объемов теней. Рендерит объемы для определения, какие части сцены находятся в тени.

+ Z-Pass Shadow Volumes: Традиционная методика, где фронтальные и задние грани объемов рендерятся для определения теней.

+ Z-Fail Shadow Volumes (Carmack's Reverse): Альтернативная методика, которая лучше справляется с объектами, пересекающими near plane (ближнюю плоскость отсечения).

3. Ray Traced Shadows (Рей трассинг теней)

+ Hard Shadows: Базовый метод, при котором тень определяется пересечением лучей с объектами сцены.

+ Soft Shadows: Более сложный метод, учитывающий площадь источника света и создающий мягкие тени.

4. Deep Shadow Maps
Используется в основном для теней от полупрозрачных объектов (например, волос, листвы). Хранит информацию о прозрачности на разных глубинах.

5. Cascaded Shadow Maps (CSM)
Улучшенный метод теневых карт для больших сцен. Делит сцену на несколько частей (каскадов), каждая из которых имеет свою теневую карту, для улучшения разрешения теней на разном удалении от камеры.

6. Cube Shadow Mapping
Использует кубическую карту для создания теней от точечных источников света.

7. Shadow Mapping with Moment Shadow Maps (MSM)
Усовершенствование VSM, использует моменты для представления теней и уменьшения утечек света.

8. Hybrid Algorithms
Hybrid Rendering: Комбинация различных алгоритмов (например, использование Shadow Mapping для статических объектов и Ray Tracing для динамических).

9. Penumbra Wedges
Метод для создания мягких теней путем вычисления области полутени (penumbra) между объектами и источником света.

10.   Light Space Perspective Shadow Maps (LiSPSM)
Улучшение теневых карт, использующее перспективное искажение для увеличения разрешения теней вблизи камеры.

11.   Contact Hardening Shadows
Метод для создания теней, которые становятся жестче по мере приближения к объекту, который их отбрасывает.
