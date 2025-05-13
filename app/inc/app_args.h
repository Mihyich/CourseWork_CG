#ifndef APP_ARGS_H
#define APP_ARGS_H

#include <Windows.h>
#include <vector>

#include "winapi_window.h"
#include "winapi_GLwindow.h"
#include "winapi_font.h"

#define AUTOR_CAPTION \
L"\
Автор\
"

#define AUTOR_TEXT \
L"\
Студент: Зевахин Михаил Евгеньевич\n\
Группа:  ИУ7-45Б\
"

#define HIT_BORDER_SIZE 10

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
    extern LONG ToolbarMinWidth;
    extern LONG ToolbarWidth; // Ширина окна toolbar

    // Окно найстроки теней
    extern WinApiWindow ShadowWnd;
    extern WinApiWindow ShadowMapWnd;   // =============
    extern WinApiWindow RayTracingWnd;  // дочерние окна
    extern WinApiWindow PathTracingWnd; // =============

    // Общее окно настроек теней (для всех алгоритмов)
    extern WinApiWindow GeneralShadowOptionsWnd;

    // Окно настройки освещения
    extern WinApiWindow LightingWnd;

    // Окно настройки модели
    extern WinApiWindow ModelWnd;

    // Рендер окно
    extern WinApiGLWindow RenderWnd;

    // Частота кадров
    extern int framePerSecond;

    // шрифты
    extern WinApiFont Fonts;
}

#endif //APP_ARGS_H