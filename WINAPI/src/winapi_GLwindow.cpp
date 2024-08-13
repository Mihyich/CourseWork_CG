#include "winapi_GLwindow.h"

BOOL WinApiGLWindow::check_wndclass_options(void)
{
    WNDCLASSEX wcx;

    // Проверить, что класс вообще существует
    if (!GetClassInfoEx(this->hInstance, this->ClassName.c_str(), &wcx))
        return FALSE;

    // Проверка стиля класса
    if (!(wcx.style & CS_OWNDC))
        return FALSE;

    return TRUE;
}

BOOL WinApiGLWindow::check_resources_readiness(void)
{
    return IsWindow(this->hWnd) && wglGetCurrentContext();
}

WinApiGLWindow::WinApiGLWindow()
{
    ZeroMemory(&msg, sizeof(MSG));
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
}

WinApiGLWindow::~WinApiGLWindow()
{
    reset_and_free_data();
}

BOOL WinApiGLWindow::CreateOpenGLContext(void)
{
    HDC hDC = NULL;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL; // расширение WGL_ARB_create_context

    // Проверка совместимости класса
    if (!check_wndclass_options())
        return ERR_WNDCLASS_DISMATCH;

    // Получение контекста устройства (Device Context)
    if ((hDC = GetDC(hWnd)) == NULL)
    {
        error = GetLastError();
        return ERR_HDCNOTGOTTEN;
    }

    // Настройка и установка формата пискселей формата пикселей
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_GENERIC_ACCELERATED | PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE | PFD_SUPPORT_COMPOSITION;
    // pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 16;
    pfd.cStencilBits = 8;
    INT pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (!pixelFormat || !SetPixelFormat(hDC, pixelFormat, &pfd))
    {
        error = GetLastError();
        return ERR_PIXELFORMAT;
    }

    // Создание временного контекста OpenGL,
    // он нужен для получения функции wglCreateContextAttribsARB
    hRC = wglCreateContext(hDC);
    if (!hRC || !wglMakeCurrent(hDC, hRC))
    {
        error = GetLastError();
        return ERR_WGLTEMPCONTEXT;
    }

    // Запрос на расширение WGL_ARB_create_context
    OPENGL_GET_PROC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
    if (!wglCreateContextAttribsARB)
    {
        error = GetLastError();
        return ERR_PFNWGLCREATE;
    }

    // Теперь временный контекст больше не нужен
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);

    // Атрибуты для создания расширенного контекста OpenGL
    INT attribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    // Создание современного контекста OpenGL
    hRC = wglCreateContextAttribsARB(hDC, NULL, attribs);
    if (!hRC || !wglMakeCurrent(hDC, hRC))
    {
        error = GetLastError();
        return ERR_WGLCONTEXT;
    }

    // Загрузка всех необходимых расширений OpenGL
    if (!gl_init_extensions())
    {
        g_OpenGLError = glGetError();
        return ERR_EXTENSIONS;
    }

    return OPENGL_CONTEXT_CREATED;
}

VOID WinApiGLWindow::Destroy()
{
    // Удаляем контекст рендеринга
    if (hRC)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hRC);
        hRC = NULL;
    }

    // Удаляем окно
    if (hWnd)
    {
        DestroyWindow(hWnd);
        hWnd = NULL;
    }

    // Удаляем класс окна
    WNDCLASSEX wcx;
    if (GetClassInfoEx(this->hInstance, this->ClassName.c_str(), &wcx))
    {
        UnregisterClass(wcx.lpszClassName, wcx.hInstance);
    }

    // Очистка структур
    ZeroMemory(&this->msg, sizeof(MSG));
    ZeroMemory(&this->pfd, sizeof(PIXELFORMATDESCRIPTOR));
}

VOID WinApiGLWindow::reset_and_free_data(void)
{
    // Удаление контекста рендеринга
    if (this->hRC)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(this->hRC);
    }
    this->hRC = NULL;

    // Удаляем окно
    if (this->hWnd)
        DestroyWindow(this->hWnd);
    this->hWnd = NULL;

    // Удаляем класс окна
    WNDCLASSEX wcx;
    if (GetClassInfoEx(this->hInstance, this->ClassName.c_str(), &wcx))
        UnregisterClass(this->ClassName.c_str(), this->hInstance);
    ClassName.clear();
    hInstance = NULL;

    // почистить таблицу акселераторов
    if (this->hAccel)
        DestroyAcceleratorTable(this->hAccel);
    this->hAccel = NULL;

    // очистка структур
    ZeroMemory(&this->msg, sizeof(MSG));
    ZeroMemory(&this->pfd, sizeof(PIXELFORMATDESCRIPTOR));
}