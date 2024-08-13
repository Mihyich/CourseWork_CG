#ifndef WINAPI_GLWINDOW_H
#define WINAPI_GLWINDOW_H

#include <math.h>

#include "winapi_window.h"
#include "winapi_GLextensions.h"
#include "winapi_mouse.h"

#define OPENGL_CONTEXT_CREATED 0 // контекст и расширения успешно установлены
#define ERR_WNDCLASS_DISMATCH 1  // окно имеет неподходящий класс для OpenGL
#define ERR_HDCNOTGOTTEN 2       // ошибка получения контекста устройства
#define ERR_PIXELFORMAT 3        // ошибка установки пиксельного формата
#define ERR_WGLTEMPCONTEXT 4     // ошибка установки временного контекста OpenGL
#define ERR_PFNWGLCREATE 5       // ошибка получения расширения WGL_ARB_create_context
#define ERR_WGLCONTEXT 6         // ошибка установки расширенного контекста OpenGL
#define ERR_EXTENSIONS 7         // ошибка при загрузке расширений

class WinApiGLWindow : public WinApiWindow
{
private:
    HGLRC hRC = NULL; // контекст рендеринга
    MSG msg; // структура системный сообщений

    PIXELFORMATDESCRIPTOR pfd; // формат пикселей

    BOOL check_wndclass_options(void);
    BOOL check_resources_readiness(void);

public:
    WinApiGLWindow();
    ~WinApiGLWindow();

    BOOL CreateOpenGLContext(void);

    VOID Destroy() override;

protected:
    VOID reset_and_free_data(void) override;
};

#endif // WINAPI_GLWINDOW_H