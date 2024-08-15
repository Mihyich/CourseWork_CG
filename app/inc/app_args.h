#ifndef APP_ARGS_H
#define APP_ARGS_H

#include <Windows.h>
#include <vector>

#include "winapi_window.h"
#include "winapi_GLwindow.h"
#include "winapi_font.h"

#define AUTOR \
L"Автор"

#define AUTOR_CAPTION \
L"Студент: Зевахин Михаил Евгеньевич\n\
Группа:  ИУ7-45Б"

#define TASK_NOMER \
L"Вариант №--"

#define TASK_CAPTION \
L"Реализация алгоритма плавающего горизонта."

#define INSTRUCTION_HEADER \
L"Инструкция"

#define INSTRUCTION_CAPTION_INPUT \
L"Ввод данных:\n\
1. Выбрать формулу поверхности из списка\n\
2. Ввести диапазон X в формате \"point\"\n\
3. Ввести диапазон Z в формате \"point\"\n\
4. Ввести шаг X в формате \"float\"\n\
5. Ввести шаг Z в формате \"float\"\n\
6. Выбрать цвет поверхности\n\
7. Кнопка \"Нарисовать\"\n\n\
Прокрутка поверхности:\n\
1. LBM + MOVE\n\n\
Масштаб поверхности:\n\
1. WHEEL"

#define INSTRUCTION_CAPTION_FORMAT \
L"Формат \"float\":\n\
1. {+/-}{1-7 цифр в целой части}.{1-6 цифр в дробной}\n\
2. Знак можно не указывать\n\
3. Можно вводить число без дробной части\n\
4. При вводе целого числа - дробную точку исключить\n\
\n\
Формат \"point\":\n\
1. 2 числа в формате \"float\" разделенные символами табуляции"

#define INSTRUCTION_CAPTION_COORD_SYSTEM \
L"Система координат *:\n\
1. Перемещение: Отсутствует\n\
2. Масштабирование: WHEEL\n\
3. Используйте стандартные действия в меню \"графика\""

// отправка данных координат мыши
#define MAX_COORD_MSG_LEN 15
#define MAX_COORD_VALUE_LEN 12

// отправка данных коэффициента масштабирования
#define MAX_SCALE_MSG_LEN 14
#define MAX_SCALE_VALUE_LEN 7

namespace app
{
    // Дескриптор приложения
    extern HINSTANCE hInst;
    // командная строка
    extern PSTR lpCmdLine;

    // Основное окно
    extern WinApiWindow MainWnd;
    extern const POINT MinMainWndSize; // Минимальный размер род. окна

    // Окно инструментов
    extern WinApiWindow ToolbarWnd;
    extern LONG ToolbarWidth; // Ширина окна toolbar
    // его дочерние окна ...

    // Рендер окно
    extern WinApiGLWindow RenderWnd;

    // шрифты
    extern WinApiFont Fonts;
}

#endif //APP_ARGS_H