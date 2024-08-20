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
}

WinApiGLWindow::~WinApiGLWindow()
{
    reset_and_free_data();
}

BOOL WinApiGLWindow::CreateOpenGLContext()
{
    HDC hDC = NULL;
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

    INT PixelFormat = 0;
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), // Размер структуры в байтах
        1, //  Версия структуры
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Флаги, определяющие свойства формата пикселей
        PFD_TYPE_RGBA, // Тип пикселей
        32, // Количество битов на цвет в буфере цветов
        0, // Количество битов, используемых для красного компонента
        0, // Смещение красного компонента
        0, // Количество битов, используемых для зеленого компонента
        0, // Смещение зеленого компонента
        0, // Количество битов, используемых для синего компонента
        0, // Смещение синего компонента
        0, // Количество битов, используемых для альфа-компонента
        0, // Смещение альфа-компонента
        0, // Общее количество битов в накопительном буфере
        0, // Количество битов, используемых для красного компонента в накопительном буфере
        0, // Количество битов, используемых для зеленого компонента в накопительном буфере
        0, // Количество битов, используемых для синего компонента в накопительном буфере
        0, // Количество битов, используемых для альфа-компонента в накопительном буфере
        32, // Количество битов в буфере глубины
        8, // Количество битов в буфере трафарета
        0, // Количество вспомогательных буферов
        PFD_MAIN_PLANE, // Уровень поверхности
        0, // Зарезервировано
        0, // Маска для уровня поверхности
        0, // Маска видимости
        0 // Маска повреждений
    };

    // Атрибуты для создания расширенного контекста OpenGL
    INT modernContextAttribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    // Проверка совместимости класса
    if (!check_wndclass_options())
        return ERR_WNDCLASS_DISMATCH;

    // Получение контекста устройства
    if ((hDC = GetDC(hWnd)) == NULL)
    {
        error = GetLastError();
        return ERR_HDCNOTGOTTEN;
    }

    // Установка временного пиксельного формата
    PixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (!PixelFormat || !SetPixelFormat(hDC, PixelFormat, &pfd))
    {
        error = GetLastError();
        return ERR_PIXELFORMAT;
    }

    // Создание временного контекста OpenGL
    hRC = wglCreateContext(hDC);
    if (!hRC || !wglMakeCurrent(hDC, hRC))
    {
        error = GetLastError();
        return ERR_WGLTEMPCONTEXT;
    }

    // Загрузка расширения
    OPENGL_GET_PROC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
    if (!wglCreateContextAttribsARB)
    {
        error = GetLastError();
        return ERR_PFNWGLCREATE;
    }

    // Загрузка расширения
    OPENGL_GET_PROC(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
    if (!wglChoosePixelFormatARB)
    {
        error = GetLastError();
        return ERR_PFNWGLCREATE;
    }

    DisableAeroForWindow(hWnd);  

    // Теперь временный контекст больше не нужен
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);

    // Создание современного контекста OpenGL
    hRC = wglCreateContextAttribsARB(hDC, NULL, modernContextAttribs);
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
}