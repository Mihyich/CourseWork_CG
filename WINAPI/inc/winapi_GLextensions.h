#ifndef WINAPI_GLEXTENSIONS_H
#define WINAPI_GLEXTENSIONS_H

#define WIN32_LEAN_AND_MEAN 1 // Урезанный windows.h
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <windows.h>
#include <string>
#include <list>
// #include "logger.h"

// переменная для хранения ошибок OpenGL
extern GLenum g_OpenGLError;

/// @brief Данные текущего контекста OpenGL
struct opengl_context_info
{
    const GLubyte *gl_version = nullptr;   // Версия OpenGL
    const GLubyte *gl_renderer = nullptr;  // Средство визуализации OpenGL
    const GLubyte *gl_vendor = nullptr;    // Изготовитель
    const GLubyte *glsl_version = nullptr; // Версия GLSL
    GLint major_version = 0;  // Мажорная версия
    GLint minor_version = 0;   // Минорная версия
    GLint num_extensions = 0; // Кол-во расширений
};

// Расширения OpenGL
 
// Расширения
extern PFNGLGETSTRINGIPROC glGetStringi;
// Время
extern PFNGLGENQUERIESPROC glGenQueries;
extern PFNGLBEGINQUERYPROC glBeginQuery;
extern PFNGLENDQUERYPROC glEndQuery;
extern PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v;
extern PFNGLDELETEQUERIESPROC glDeleteQueries;
// Частота обновления кадров
extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
extern PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;
// Тектуры
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
// Объект массива вершин
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
// Вершинный буфер
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
// Кадровый буфер
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
// Рендер буфер
extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
// Шейдеры
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
extern PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLISSHADERPROC glIsShader;
extern PFNGLISPROGRAMPROC glIsProgram;
// распределение униформ по шейдерам
extern PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv;
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv;
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName;
// Shaders attributes
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
// Shaders uniforms
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLUNIFORM3IPROC glUniform3i;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLUNIFORM1UIPROC glUniform1ui;
extern PFNGLUNIFORM2UIPROC glUniform2ui;
extern PFNGLUNIFORM3UIPROC glUniform3ui;
extern PFNGLUNIFORM4UIPROC glUniform4ui;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM1DPROC glUniform1d;
extern PFNGLUNIFORM2DPROC glUniform2d;
extern PFNGLUNIFORM3DPROC glUniform3d;
extern PFNGLUNIFORM4DPROC glUniform4d;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORM1UIVPROC glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC glUniform4uiv;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORM1DVPROC glUniform1dv;
extern PFNGLUNIFORM2DVPROC glUniform2dv;
extern PFNGLUNIFORM3DVPROC glUniform3dv;
extern PFNGLUNIFORM4DVPROC glUniform4dv;
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
// Униформные блоки
extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;

// получть адрес функции из драйвера
// #n - строкатизация, пример: abc -> "abc"
#define OPENGL_GET_PROC(p, n) n = reinterpret_cast<p>(reinterpret_cast<void (*)()>(wglGetProcAddress(#n)));

// получть адрес функции из драйвера
// c возратом FALSE при неуспешной попытке
#define OPENGL_GET_PROC_WITH_TRHOW(p, n)                                          \
    n = reinterpret_cast<p>(reinterpret_cast<void (*)()>(wglGetProcAddress(#n))); \
    if (!n)                                                                       \
        return FALSE;

// проверка на ошибки OpenGL
#define OPENGL_CHECK_FOR_ERRORS() g_OpenGLError = glGetError();

/// @brief Загрузка расширений
/// @return флаг:
/// TRUE - если был получен адресс каждой функции
/// FALSE - хотя бы одна функция не была получена корректно
BOOL gl_init_extensions();

/// @brief Загрузить данные о текущем контексте OpenGL
/// @param data - Специальная структра данных OpenGL
GLvoid gl_init_opengl_context_info(opengl_context_info *data);

/// @brief Проверить поддержку расширений на текущем устройстве
/// @param logger - Логгер, через который ведется запись (файл должен быт уже создан)
/// @param data - Специальная структра данных OpenGL
/// @return Флаг успешности поддержки
// BOOL gl_check_extensions_support(logger * log, opengl_context_info * data);

/// @brief Записть доступные расширения OpenGL
/// @param log - Логгер, через который ведется запись (файл должен быт уже создан)
// VOID log_extension_list(logger * log);

/// @brief Записать информацию о текущем активно контексте OpenGL
/// @param log - Логгер, через который ведется запись (файл должен быт уже создан)
/// @param data -  Специальная структра данных OpenGL
// VOID log_opengl_info(logger *log, opengl_context_info *data);

#endif // WINAPI_GLEXTENSIONS_H