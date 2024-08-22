#include "winapi_GLextensions.h"

GLenum g_OpenGLError = GL_NO_ERROR;

// Расширения OpenGL

// Расширения
PFNGLGETSTRINGIPROC glGetStringi = NULL;
// Время
PFNGLGENQUERIESPROC glGenQueries = NULL;
PFNGLBEGINQUERYPROC glBeginQuery = NULL;
PFNGLENDQUERYPROC glEndQuery = NULL;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = NULL;
PFNGLDELETEQUERIESPROC glDeleteQueries = NULL;
// Частота обновления кадров
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = NULL;
// Тектуры
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
// Объект массива вершин
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
// Вершинный буфер
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = NULL;
// Кадровый буфер
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
// Рендер буфер
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = NULL;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = NULL;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = NULL;
// Шейдеры
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = NULL;
PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = NULL;
PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLISSHADERPROC glIsShader = NULL;
PFNGLISPROGRAMPROC glIsProgram = NULL;
// распределение униформ по шейдерам
PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName = NULL;
// Shaders attributes
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
// Shaders uniforms
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM3IPROC glUniform3i = NULL;
PFNGLUNIFORM4IPROC glUniform4i = NULL;
PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORM4FPROC glUniform4f = NULL;
PFNGLUNIFORM1DPROC glUniform1d = NULL;
PFNGLUNIFORM2DPROC glUniform2d = NULL;
PFNGLUNIFORM3DPROC glUniform3d = NULL;
PFNGLUNIFORM4DPROC glUniform4d = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORM1DVPROC glUniform1dv = NULL;
PFNGLUNIFORM2DVPROC glUniform2dv = NULL;
PFNGLUNIFORM3DVPROC glUniform3dv = NULL;
PFNGLUNIFORM4DVPROC glUniform4dv = NULL;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
// Униформные блоки
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = NULL;

BOOL gl_init_extensions()
{
    // Расширения
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETSTRINGIPROC, glGetStringi);
    // Время
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGENQUERIESPROC, glGenQueries);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBEGINQUERYPROC, glBeginQuery);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLENDQUERYPROC, glEndQuery);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETEQUERIESPROC, glDeleteQueries);
    // Частота обновления кадров
    OPENGL_GET_PROC_WITH_TRHOW(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT);
    OPENGL_GET_PROC_WITH_TRHOW(PFNWGLGETSWAPINTERVALEXTPROC, wglGetSwapIntervalEXT);
    // Тектуры
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLACTIVETEXTUREPROC, glActiveTexture);
    // Объект массива вершин
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
    // Вершинный буфер
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGENBUFFERSPROC, glGenBuffers);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBINDBUFFERPROC, glBindBuffer);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBUFFERDATAPROC, glBufferData);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange);
    // Кадровый буфер
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
    // Рендер буфер
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers);
    // Шейдеры
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLCREATEPROGRAMPROC, glCreateProgram);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLLINKPROGRAMPROC, glLinkProgram);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUSEPROGRAMPROC, glUseProgram);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETSHADERIVPROC, glGetShaderiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLCREATESHADERPROC, glCreateShader);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDELETESHADERPROC, glDeleteShader);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLSHADERSOURCEPROC, glShaderSource);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLCOMPILESHADERPROC, glCompileShader);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLATTACHSHADERPROC, glAttachShader);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDETACHSHADERPROC, glDetachShader);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLISSHADERPROC, glIsShader);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLISPROGRAMPROC, glIsProgram);
    // распределение юниформ по шейдерам
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETPROGRAMSTAGEIVPROC, glGetProgramStageiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC, glGetActiveSubroutineUniformiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC, glGetActiveSubroutineUniformName);
    // Shaders attributes
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
    // Shaders uniforms
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1IPROC, glUniform1i);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2IPROC, glUniform2i);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3IPROC, glUniform3i);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4IPROC, glUniform4i);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1UIPROC, glUniform1ui);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2UIPROC, glUniform2ui);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3UIPROC, glUniform3ui);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4UIPROC, glUniform4ui);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1FPROC, glUniform1f);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2FPROC, glUniform2f);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3FPROC, glUniform3f);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4FPROC, glUniform4f);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1DPROC, glUniform1d);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2DPROC, glUniform2d);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3DPROC, glUniform3d);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4DPROC, glUniform4d);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1IVPROC, glUniform1iv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2IVPROC, glUniform2iv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3IVPROC, glUniform3iv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4IVPROC, glUniform4iv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1UIVPROC, glUniform1uiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2UIVPROC, glUniform2uiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3UIVPROC, glUniform3uiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4UIVPROC, glUniform4uiv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1FVPROC, glUniform1fv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2FVPROC, glUniform2fv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3FVPROC, glUniform3fv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4FVPROC, glUniform4fv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM1DVPROC, glUniform1dv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM2DVPROC, glUniform2dv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM3DVPROC, glUniform3dv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORM4DVPROC, glUniform4dv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
    // Униформные блоки
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex);
    OPENGL_GET_PROC_WITH_TRHOW(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding);

    OPENGL_CHECK_FOR_ERRORS();

    return TRUE;
}

GLvoid gl_init_opengl_context_info(opengl_context_info *data)
{
    data->gl_version = glGetString(GL_VERSION);
    data->gl_renderer = glGetString(GL_RENDERER);
    data->gl_vendor = glGetString(GL_VENDOR);
    data->glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    glGetIntegerv(GL_MAJOR_VERSION, &data->major_version);
    glGetIntegerv(GL_MINOR_VERSION, &data->minor_version);
    glGetIntegerv(GL_NUM_EXTENSIONS, &data->num_extensions);
}

/*
BOOL gl_check_extensions_support(logger *log, opengl_context_info *data)
{
    // Расширения, которые должны поддерживаться на устройстве
    const GLubyte *exts[] =
    {
        reinterpret_cast<const GLubyte *>("GL_AMD_multi_draw_indirect"),
        reinterpret_cast<const GLubyte *>("GL_AMD_seamless_cubemap_per_texture"),
        reinterpret_cast<const GLubyte *>("GL_AMD_vertex_shader_viewport_index"),
        reinterpret_cast<const GLubyte *>("GL_AMD_vertex_shader_layer"),
        reinterpret_cast<const GLubyte *>("GL_ARB_arrays_of_arrays"),
        reinterpret_cast<const GLubyte *>("GL_ARB_base_instance"),
        reinterpret_cast<const GLubyte *>("GL_ARB_bindless_texture"),
        reinterpret_cast<const GLubyte *>("GL_ARB_blend_func_extended"),
        reinterpret_cast<const GLubyte *>("GL_ARB_buffer_storage"),
        reinterpret_cast<const GLubyte *>("GL_ARB_clear_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_clear_texture"),
        reinterpret_cast<const GLubyte *>("GL_ARB_clip_control"),
        reinterpret_cast<const GLubyte *>("GL_ARB_color_buffer_float"),
        reinterpret_cast<const GLubyte *>("GL_ARB_compressed_texture_pixel_storage"),
        reinterpret_cast<const GLubyte *>("GL_ARB_conservative_depth"),
        reinterpret_cast<const GLubyte *>("GL_ARB_compute_shader"),
        reinterpret_cast<const GLubyte *>("GL_ARB_compute_variable_group_size"),
        reinterpret_cast<const GLubyte *>("GL_ARB_conditional_render_inverted"),
        reinterpret_cast<const GLubyte *>("GL_ARB_copy_buffer"),
        reinterpret_cast<const GLubyte *>("GL_ARB_copy_image"),
        reinterpret_cast<const GLubyte *>("GL_ARB_cull_distance"),
        reinterpret_cast<const GLubyte *>("GL_ARB_debug_output"),
        reinterpret_cast<const GLubyte *>("GL_ARB_depth_buffer_float"),
        reinterpret_cast<const GLubyte *>("GL_ARB_depth_clamp"),
        reinterpret_cast<const GLubyte *>("GL_ARB_depth_texture"),
        reinterpret_cast<const GLubyte *>("GL_ARB_derivative_control"),
        reinterpret_cast<const GLubyte *>("GL_ARB_direct_state_access"),
        reinterpret_cast<const GLubyte *>("GL_ARB_draw_buffers"),
        reinterpret_cast<const GLubyte *>("GL_ARB_draw_buffers_blend"),
        reinterpret_cast<const GLubyte *>("GL_ARB_draw_indirect"),
        reinterpret_cast<const GLubyte *>("GL_ARB_draw_elements_base_vertex"),
        reinterpret_cast<const GLubyte *>("GL_ARB_draw_instanced"),
        reinterpret_cast<const GLubyte *>("GL_ARB_enhanced_layouts"),
        reinterpret_cast<const GLubyte *>("GL_ARB_ES2_compatibility"),
        reinterpret_cast<const GLubyte *>("GL_ARB_ES3_compatibility"),
        reinterpret_cast<const GLubyte *>("GL_ARB_ES3_1_compatibility"),
        reinterpret_cast<const GLubyte *>("GL_ARB_ES3_2_compatibility"),
        reinterpret_cast<const GLubyte *>("GL_ARB_explicit_attrib_location"),
        reinterpret_cast<const GLubyte *>("GL_ARB_explicit_uniform_location"),
        reinterpret_cast<const GLubyte *>("GL_ARB_fragment_coord_conventions"),
        reinterpret_cast<const GLubyte *>("GL_ARB_fragment_layer_viewport"),
        reinterpret_cast<const GLubyte *>("GL_ARB_fragment_program"),
        reinterpret_cast<const GLubyte *>("GL_ARB_fragment_program_shadow"),
        reinterpret_cast<const GLubyte *>("GL_ARB_fragment_shader"),
        reinterpret_cast<const GLubyte *>("GL_ARB_fragment_shader_interlock"),
        reinterpret_cast<const GLubyte *>("GL_ARB_framebuffer_no_attachments"),
        reinterpret_cast<const GLubyte *>("GL_ARB_framebuffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_framebuffer_sRGB"),
        reinterpret_cast<const GLubyte *>("GL_ARB_geometry_shader4"),
        reinterpret_cast<const GLubyte *>("GL_ARB_get_program_binary"),
        reinterpret_cast<const GLubyte *>("GL_ARB_get_texture_sub_image"),
        reinterpret_cast<const GLubyte *>("GL_ARB_gl_spirv"),
        reinterpret_cast<const GLubyte *>("GL_ARB_gpu_shader5"),
        reinterpret_cast<const GLubyte *>("GL_ARB_gpu_shader_fp64"),
        reinterpret_cast<const GLubyte *>("GL_ARB_gpu_shader_int64"),
        reinterpret_cast<const GLubyte *>("GL_ARB_half_float_pixel"),
        reinterpret_cast<const GLubyte *>("GL_ARB_half_float_vertex"),
        reinterpret_cast<const GLubyte *>("GL_ARB_imaging"),
        reinterpret_cast<const GLubyte *>("GL_ARB_indirect_parameters"),
        reinterpret_cast<const GLubyte *>("GL_ARB_instanced_arrays"),
        reinterpret_cast<const GLubyte *>("GL_ARB_internalformat_query"),
        reinterpret_cast<const GLubyte *>("GL_ARB_internalformat_query2"),
        reinterpret_cast<const GLubyte *>("GL_ARB_invalidate_subdata"),
        reinterpret_cast<const GLubyte *>("GL_ARB_map_buffer_alignment"),
        reinterpret_cast<const GLubyte *>("GL_ARB_map_buffer_range"),
        reinterpret_cast<const GLubyte *>("GL_ARB_multi_bind"),
        reinterpret_cast<const GLubyte *>("GL_ARB_multi_draw_indirect"),
        reinterpret_cast<const GLubyte *>("GL_ARB_multisample"),
        reinterpret_cast<const GLubyte *>("GL_ARB_multitexture"),
        reinterpret_cast<const GLubyte *>("GL_ARB_occlusion_query"),
        reinterpret_cast<const GLubyte *>("GL_ARB_occlusion_query2"),
        reinterpret_cast<const GLubyte *>("GL_ARB_parallel_shader_compile"),
        reinterpret_cast<const GLubyte *>("GL_ARB_pipeline_statistics_query"),
        reinterpret_cast<const GLubyte *>("GL_ARB_pixel_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_point_parameters"),
        reinterpret_cast<const GLubyte *>("GL_ARB_point_sprite"),
        reinterpret_cast<const GLubyte *>("GL_ARB_polygon_offset_clamp"),
        reinterpret_cast<const GLubyte *>("GL_ARB_post_depth_coverage"),
        reinterpret_cast<const GLubyte *>("GL_ARB_program_interface_query"),
        reinterpret_cast<const GLubyte *>("GL_ARB_provoking_vertex"),
        reinterpret_cast<const GLubyte *>("GL_ARB_query_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_robust_buffer_access_behavior"),
        reinterpret_cast<const GLubyte *>("GL_ARB_robustness"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sample_locations"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sample_shading"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sampler_objects"),
        reinterpret_cast<const GLubyte *>("GL_ARB_seamless_cube_map"),
        reinterpret_cast<const GLubyte *>("GL_ARB_seamless_cubemap_per_texture"),
        reinterpret_cast<const GLubyte *>("GL_ARB_separate_shader_objects"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_atomic_counter_ops"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_atomic_counters"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_ballot"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_bit_encoding"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_clock"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_draw_parameters"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_group_vote"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_image_load_store"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_image_size"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_objects"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_precision"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_storage_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_subroutine"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_texture_image_samples"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_texture_lod"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shading_language_100"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shader_viewport_layer_array"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shading_language_420pack"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shading_language_include"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shading_language_packing"),
        reinterpret_cast<const GLubyte *>("GL_ARB_shadow"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sparse_buffer"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sparse_texture"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sparse_texture2"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sparse_texture_clamp"),
        reinterpret_cast<const GLubyte *>("GL_ARB_spirv_extensions"),
        reinterpret_cast<const GLubyte *>("GL_ARB_stencil_texturing"),
        reinterpret_cast<const GLubyte *>("GL_ARB_sync"),
        reinterpret_cast<const GLubyte *>("GL_ARB_tessellation_shader"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_barrier"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_border_clamp"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_buffer_object_rgb32"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_buffer_range"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_compression"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_compression_bptc"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_compression_rgtc"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_cube_map"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_cube_map_array"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_env_add"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_env_combine"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_env_crossbar"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_env_dot3"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_filter_anisotropic"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_filter_minmax"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_float"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_gather"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_mirror_clamp_to_edge"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_mirrored_repeat"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_multisample"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_non_power_of_two"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_query_levels"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_query_lod"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_rectangle"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_rg"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_rgb10_a2ui"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_stencil8"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_storage"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_storage_multisample"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_swizzle"),
        reinterpret_cast<const GLubyte *>("GL_ARB_texture_view"),
        reinterpret_cast<const GLubyte *>("GL_ARB_timer_query"),
        reinterpret_cast<const GLubyte *>("GL_ARB_transform_feedback2"),
        reinterpret_cast<const GLubyte *>("GL_ARB_transform_feedback3"),
        reinterpret_cast<const GLubyte *>("GL_ARB_transform_feedback_instanced"),
        reinterpret_cast<const GLubyte *>("GL_ARB_transform_feedback_overflow_query"),
        reinterpret_cast<const GLubyte *>("GL_ARB_transpose_matrix"),
        reinterpret_cast<const GLubyte *>("GL_ARB_uniform_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_array_bgra"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_array_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_attrib_64bit"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_attrib_binding"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_program"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_shader"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_type_10f_11f_11f_rev"),
        reinterpret_cast<const GLubyte *>("GL_ARB_vertex_type_2_10_10_10_rev"),
        reinterpret_cast<const GLubyte *>("GL_ARB_viewport_array"),
        reinterpret_cast<const GLubyte *>("GL_ARB_window_pos"),
        reinterpret_cast<const GLubyte *>("GL_ATI_draw_buffers"),
        reinterpret_cast<const GLubyte *>("GL_ATI_texture_float"),
        reinterpret_cast<const GLubyte *>("GL_ATI_texture_mirror_once"),
        reinterpret_cast<const GLubyte *>("GL_S3_s3tc"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_env_add"),
        reinterpret_cast<const GLubyte *>("GL_EXT_abgr"),
        reinterpret_cast<const GLubyte *>("GL_EXT_bgra"),
        reinterpret_cast<const GLubyte *>("GL_EXT_bindable_uniform"),
        reinterpret_cast<const GLubyte *>("GL_EXT_blend_color"),
        reinterpret_cast<const GLubyte *>("GL_EXT_blend_equation_separate"),
        reinterpret_cast<const GLubyte *>("GL_EXT_blend_func_separate"),
        reinterpret_cast<const GLubyte *>("GL_EXT_blend_minmax"),
        reinterpret_cast<const GLubyte *>("GL_EXT_blend_subtract"),
        reinterpret_cast<const GLubyte *>("GL_EXT_compiled_vertex_array"),
        reinterpret_cast<const GLubyte *>("GL_EXT_Cg_shader"),
        reinterpret_cast<const GLubyte *>("GL_EXT_depth_bounds_test"),
        reinterpret_cast<const GLubyte *>("GL_EXT_direct_state_access"),
        reinterpret_cast<const GLubyte *>("GL_EXT_draw_buffers2"),
        reinterpret_cast<const GLubyte *>("GL_EXT_draw_instanced"),
        reinterpret_cast<const GLubyte *>("GL_EXT_draw_range_elements"),
        reinterpret_cast<const GLubyte *>("GL_EXT_fog_coord"),
        reinterpret_cast<const GLubyte *>("GL_EXT_framebuffer_blit"),
        reinterpret_cast<const GLubyte *>("GL_EXT_framebuffer_multisample"),
        reinterpret_cast<const GLubyte *>("GL_EXTX_framebuffer_mixed_formats"),
        reinterpret_cast<const GLubyte *>("GL_EXT_framebuffer_multisample_blit_scaled"),
        reinterpret_cast<const GLubyte *>("GL_EXT_framebuffer_object"),
        reinterpret_cast<const GLubyte *>("GL_EXT_framebuffer_sRGB"),
        reinterpret_cast<const GLubyte *>("GL_EXT_geometry_shader4"),
        reinterpret_cast<const GLubyte *>("GL_EXT_gpu_program_parameters"),
        reinterpret_cast<const GLubyte *>("GL_EXT_gpu_shader4"),
        reinterpret_cast<const GLubyte *>("GL_EXT_multi_draw_arrays"),
        reinterpret_cast<const GLubyte *>("GL_EXT_multiview_texture_multisample"),
        reinterpret_cast<const GLubyte *>("GL_EXT_multiview_timer_query"),
        reinterpret_cast<const GLubyte *>("GL_EXT_packed_depth_stencil"),
        reinterpret_cast<const GLubyte *>("GL_EXT_packed_float"),
        reinterpret_cast<const GLubyte *>("GL_EXT_packed_pixels"),
        reinterpret_cast<const GLubyte *>("GL_EXT_pixel_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_EXT_point_parameters"),
        reinterpret_cast<const GLubyte *>("GL_EXT_polygon_offset_clamp"),
        reinterpret_cast<const GLubyte *>("GL_EXT_post_depth_coverage"),
        reinterpret_cast<const GLubyte *>("GL_EXT_provoking_vertex"),
        reinterpret_cast<const GLubyte *>("GL_EXT_raster_multisample"),
        reinterpret_cast<const GLubyte *>("GL_EXT_rescale_normal"),
        reinterpret_cast<const GLubyte *>("GL_EXT_secondary_color"),
        reinterpret_cast<const GLubyte *>("GL_EXT_separate_shader_objects"),
        reinterpret_cast<const GLubyte *>("GL_EXT_separate_specular_color"),
        reinterpret_cast<const GLubyte *>("GL_EXT_shader_image_load_formatted"),
        reinterpret_cast<const GLubyte *>("GL_EXT_shader_image_load_store"),
        reinterpret_cast<const GLubyte *>("GL_EXT_shader_integer_mix"),
        reinterpret_cast<const GLubyte *>("GL_EXT_shadow_funcs"),
        reinterpret_cast<const GLubyte *>("GL_EXT_sparse_texture2"),
        reinterpret_cast<const GLubyte *>("GL_EXT_stencil_two_side"),
        reinterpret_cast<const GLubyte *>("GL_EXT_stencil_wrap"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture3D"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_array"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_compression_dxt1"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_compression_latc"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_compression_rgtc"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_compression_s3tc"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_cube_map"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_edge_clamp"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_env_combine"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_env_dot3"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_filter_anisotropic"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_filter_minmax"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_integer"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_lod"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_lod_bias"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_mirror_clamp"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_object"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_shadow_lod"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_shared_exponent"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_sRGB"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_sRGB_R8"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_sRGB_decode"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_storage"),
        reinterpret_cast<const GLubyte *>("GL_EXT_texture_swizzle"),
        reinterpret_cast<const GLubyte *>("GL_EXT_timer_query"),
        reinterpret_cast<const GLubyte *>("GL_EXT_transform_feedback2"),
        reinterpret_cast<const GLubyte *>("GL_EXT_vertex_array"),
        reinterpret_cast<const GLubyte *>("GL_EXT_vertex_array_bgra"),
        reinterpret_cast<const GLubyte *>("GL_EXT_vertex_attrib_64bit"),
        reinterpret_cast<const GLubyte *>("GL_EXT_window_rectangles"),
        reinterpret_cast<const GLubyte *>("GL_EXT_import_sync_object"),
        reinterpret_cast<const GLubyte *>("GL_IBM_rasterpos_clip"),
        reinterpret_cast<const GLubyte *>("GL_IBM_texture_mirrored_repeat"),
        reinterpret_cast<const GLubyte *>("GL_KHR_context_flush_control"),
        reinterpret_cast<const GLubyte *>("GL_KHR_debug"),
        reinterpret_cast<const GLubyte *>("GL_EXT_memory_object"),
        reinterpret_cast<const GLubyte *>("GL_EXT_memory_object_win32"),
        reinterpret_cast<const GLubyte *>("GL_NV_memory_object_sparse"),
        reinterpret_cast<const GLubyte *>("GL_EXT_win32_keyed_mutex"),
        reinterpret_cast<const GLubyte *>("GL_KHR_parallel_shader_compile"),
        reinterpret_cast<const GLubyte *>("GL_KHR_no_error"),
        reinterpret_cast<const GLubyte *>("GL_KHR_robust_buffer_access_behavior"),
        reinterpret_cast<const GLubyte *>("GL_KHR_robustness"),
        reinterpret_cast<const GLubyte *>("GL_EXT_semaphore"),
        reinterpret_cast<const GLubyte *>("GL_EXT_semaphore_win32"),
        reinterpret_cast<const GLubyte *>("GL_NV_timeline_semaphore"),
        reinterpret_cast<const GLubyte *>("GL_KHR_shader_subgroup"),
        reinterpret_cast<const GLubyte *>("GL_KTX_buffer_region"),
        reinterpret_cast<const GLubyte *>("GL_NV_alpha_to_coverage_dither_control"),
        reinterpret_cast<const GLubyte *>("GL_NV_bindless_multi_draw_indirect"),
        reinterpret_cast<const GLubyte *>("GL_NV_bindless_multi_draw_indirect_count"),
        reinterpret_cast<const GLubyte *>("GL_NV_bindless_texture"),
        reinterpret_cast<const GLubyte *>("GL_NV_blend_equation_advanced"),
        reinterpret_cast<const GLubyte *>("GL_NV_blend_equation_advanced_coherent"),
        reinterpret_cast<const GLubyte *>("GL_NVX_blend_equation_advanced_multi_draw_buffers"),
        reinterpret_cast<const GLubyte *>("GL_NV_blend_minmax_factor"),
        reinterpret_cast<const GLubyte *>("GL_NV_blend_square"),
        reinterpret_cast<const GLubyte *>("GL_NV_clip_space_w_scaling"),
        reinterpret_cast<const GLubyte *>("GL_NV_command_list"),
        reinterpret_cast<const GLubyte *>("GL_NV_compute_program5"),
        reinterpret_cast<const GLubyte *>("GL_NV_compute_shader_derivatives"),
        reinterpret_cast<const GLubyte *>("GL_NV_conditional_render"),
        reinterpret_cast<const GLubyte *>("GL_NV_conservative_raster"),
        reinterpret_cast<const GLubyte *>("GL_NV_conservative_raster_dilate"),
        reinterpret_cast<const GLubyte *>("GL_NV_conservative_raster_pre_snap"),
        reinterpret_cast<const GLubyte *>("GL_NV_conservative_raster_pre_snap_triangles"),
        reinterpret_cast<const GLubyte *>("GL_NV_conservative_raster_underestimation"),
        reinterpret_cast<const GLubyte *>("GL_NV_copy_depth_to_color"),
        reinterpret_cast<const GLubyte *>("GL_NV_copy_image"),
        reinterpret_cast<const GLubyte *>("GL_NV_depth_buffer_float"),
        reinterpret_cast<const GLubyte *>("GL_NV_depth_clamp"),
        reinterpret_cast<const GLubyte *>("GL_NV_draw_texture"),
        reinterpret_cast<const GLubyte *>("GL_NV_draw_vulkan_image"),
        reinterpret_cast<const GLubyte *>("GL_NV_ES1_1_compatibility"),
        reinterpret_cast<const GLubyte *>("GL_NV_ES3_1_compatibility"),
        reinterpret_cast<const GLubyte *>("GL_NV_explicit_multisample"),
        reinterpret_cast<const GLubyte *>("GL_NV_feature_query"),
        reinterpret_cast<const GLubyte *>("GL_NV_fence"),
        reinterpret_cast<const GLubyte *>("GL_NV_fill_rectangle"),
        reinterpret_cast<const GLubyte *>("GL_NV_float_buffer"),
        reinterpret_cast<const GLubyte *>("GL_NV_fog_distance"),
        reinterpret_cast<const GLubyte *>("GL_NV_fragment_coverage_to_color"),
        reinterpret_cast<const GLubyte *>("GL_NV_fragment_program"),
        reinterpret_cast<const GLubyte *>("GL_NV_fragment_program_option"),
        reinterpret_cast<const GLubyte *>("GL_NV_fragment_program2"),
        reinterpret_cast<const GLubyte *>("GL_NV_fragment_shader_barycentric"),
        reinterpret_cast<const GLubyte *>("GL_NV_fragment_shader_interlock"),
        reinterpret_cast<const GLubyte *>("GL_NV_framebuffer_mixed_samples"),
        reinterpret_cast<const GLubyte *>("GL_NV_framebuffer_multisample_coverage"),
        reinterpret_cast<const GLubyte *>("GL_NV_geometry_shader4"),
        reinterpret_cast<const GLubyte *>("GL_NV_geometry_shader_passthrough"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_program4"),
        reinterpret_cast<const GLubyte *>("GL_NV_internalformat_sample_query"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_program4_1"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_program5"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_program5_mem_extended"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_program_fp64"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_shader5"),
        reinterpret_cast<const GLubyte *>("GL_NV_half_float"),
        reinterpret_cast<const GLubyte *>("GL_NV_light_max_exponent"),
        reinterpret_cast<const GLubyte *>("GL_NV_memory_attachment"),
        reinterpret_cast<const GLubyte *>("GL_NV_mesh_shader"),
        reinterpret_cast<const GLubyte *>("GL_NV_multisample_coverage"),
        reinterpret_cast<const GLubyte *>("GL_NV_multisample_filter_hint"),
        reinterpret_cast<const GLubyte *>("GL_NV_occlusion_query"),
        reinterpret_cast<const GLubyte *>("GL_NV_packed_depth_stencil"),
        reinterpret_cast<const GLubyte *>("GL_NV_parameter_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_NV_parameter_buffer_object2"),
        reinterpret_cast<const GLubyte *>("GL_NV_path_rendering"),
        reinterpret_cast<const GLubyte *>("GL_NV_path_rendering_shared_edge"),
        reinterpret_cast<const GLubyte *>("GL_NV_pixel_data_range"),
        reinterpret_cast<const GLubyte *>("GL_NV_point_sprite"),
        reinterpret_cast<const GLubyte *>("GL_NV_primitive_restart"),
        reinterpret_cast<const GLubyte *>("GL_NV_query_resource"),
        reinterpret_cast<const GLubyte *>("GL_NV_query_resource_tag"),
        reinterpret_cast<const GLubyte *>("GL_NV_register_combiners"),
        reinterpret_cast<const GLubyte *>("GL_NV_register_combiners2"),
        reinterpret_cast<const GLubyte *>("GL_NV_representative_fragment_test"),
        reinterpret_cast<const GLubyte *>("GL_NV_sample_locations"),
        reinterpret_cast<const GLubyte *>("GL_NV_sample_mask_override_coverage"),
        reinterpret_cast<const GLubyte *>("GL_NV_scissor_exclusive"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_atomic_counters"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_atomic_float"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_atomic_float64"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_atomic_fp16_vector"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_atomic_int64"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_buffer_load"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_storage_buffer_object"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_subgroup_partitioned"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_texture_footprint"),
        reinterpret_cast<const GLubyte *>("GL_NV_shading_rate_image"),
        reinterpret_cast<const GLubyte *>("GL_NV_stereo_view_rendering"),
        reinterpret_cast<const GLubyte *>("GL_NV_texgen_reflection"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_barrier"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_compression_vtc"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_env_combine4"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_multisample"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_rectangle"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_rectangle_compressed"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_shader"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_shader2"),
        reinterpret_cast<const GLubyte *>("GL_NV_texture_shader3"),
        reinterpret_cast<const GLubyte *>("GL_NV_transform_feedback"),
        reinterpret_cast<const GLubyte *>("GL_NV_transform_feedback2"),
        reinterpret_cast<const GLubyte *>("GL_NV_uniform_buffer_unified_memory"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_array_range"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_array_range2"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_attrib_integer_64bit"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_buffer_unified_memory"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_program"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_program1_1"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_program2"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_program2_option"),
        reinterpret_cast<const GLubyte *>("GL_NV_vertex_program3"),
        reinterpret_cast<const GLubyte *>("GL_NV_viewport_array2"),
        reinterpret_cast<const GLubyte *>("GL_NV_viewport_swizzle"),
        reinterpret_cast<const GLubyte *>("GL_NVX_conditional_render"),
        reinterpret_cast<const GLubyte *>("GL_NVX_linked_gpu_multicast"),
        reinterpret_cast<const GLubyte *>("GL_NV_gpu_multicast"),
        reinterpret_cast<const GLubyte *>("GL_NVX_gpu_multicast2"),
        reinterpret_cast<const GLubyte *>("GL_NVX_progress_fence"),
        reinterpret_cast<const GLubyte *>("GL_NVX_gpu_memory_info"),
        reinterpret_cast<const GLubyte *>("GL_NVX_multigpu_info"),
        reinterpret_cast<const GLubyte *>("GL_NVX_nvenc_interop"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_thread_group"),
        reinterpret_cast<const GLubyte *>("GL_NV_shader_thread_shuffle"),
        reinterpret_cast<const GLubyte *>("GL_KHR_blend_equation_advanced"),
        reinterpret_cast<const GLubyte *>("GL_KHR_blend_equation_advanced_coherent"),
        reinterpret_cast<const GLubyte *>("GL_OVR_multiview"),
        reinterpret_cast<const GLubyte *>("GL_OVR_multiview2"),
        reinterpret_cast<const GLubyte *>("GL_SGIS_generate_mipmap"),
        reinterpret_cast<const GLubyte *>("GL_SGIS_texture_lod"),
        reinterpret_cast<const GLubyte *>("GL_SGIX_depth_texture"),
        reinterpret_cast<const GLubyte *>("GL_SGIX_shadow"),
        reinterpret_cast<const GLubyte *>("GL_SUN_slice_accum"),
        reinterpret_cast<const GLubyte *>("GL_WIN_swap_hint"),
        reinterpret_cast<const GLubyte *>("WGL_EXT_swap_control")
    };

    size_t count = sizeof(exts) / sizeof(exts[0]);
    const GLubyte *ext = nullptr;
    bool found;
    std::list<std::string> unworthy;
    std::list<std::string>::iterator iter;
    std::string message;
    INT contin;
    INT log_unw;
    int nomer;

    for (const GLubyte *source_ext : exts)
    {
        found = false;

        for (size_t i = 0; i < data->num_extensions; ++i)
        {
            ext = glGetStringi(GL_EXTENSIONS, i);

            if (strcmp(
                reinterpret_cast<const char *>(source_ext),
                reinterpret_cast<const char *>(ext)) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
            unworthy.emplace_back(std::string(reinterpret_cast<const char *>(source_ext)));

    }

    if (unworthy.size())
    {
        contin = MessageBox
        (
            NULL,
            L"Текущий контекст OpenGL поддерживает не все необходимые расширения. " \
            L"Некоторые компоненты программы могут работать неправильно.\n" \
            L"                                            Продолжить выполнение программы?",
            L"OpenGL_Context - предупреждение",
            MB_YESNO | MB_ICONASTERISK
        );

        log_unw = MessageBox
        (
            NULL,
            L"Сохранить названия неопределенных расширений в лог-файл?",
            L"Неподдерживаемые расширения",
            MB_YESNO
        );

        if (log_unw == IDYES)
        {
            nomer = 1;
            iter = unworthy.begin();

            for (; iter != unworthy.end(); ++iter)
            {
                message += "#" + std::to_string(nomer++) + ":\t";
                message += iter->c_str();
                message += "\n";
            }

            log->log(message.c_str());
        }

        return contin == IDYES;
    }

    return TRUE;
}

VOID log_extension_list(logger *log)
{
    int numExtensions;
    const char *extension;
    std::string message;

    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (int i = 0; i < numExtensions; ++i)
    {
        extension = reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i));
        message += std::to_string(i + 1) + ": " + extension + "\n";
    }

    log->log(message.c_str());
}

VOID log_opengl_info(logger *log, opengl_context_info *data)
{
    std::string message;

    // Составление лога
    message += "OpenGL Version:  " + (data->gl_version ? std::string(reinterpret_cast<const char *>(data->gl_version)) : "???") + "\n";
    message += "OpenGL Renderer: " + (data->gl_renderer ? std::string(reinterpret_cast<const char *>(data->gl_renderer)) : "???") + "\n";
    message += "OpenGL Vendor:   " + (data->gl_vendor ? std::string(reinterpret_cast<const char *>(data->gl_vendor)) : "???") + "\n";
    message += "OpenGL major version: " + std::to_string(data->major_version) + "\n";
    message += "OpenGL minor version: " + std::to_string(data->minor_version) + "\n";
    message += "OpenGL extension's count: " + std::to_string(data->num_extensions) + "\n";
    message += "GLSL shading language version: " + (data->glsl_version ? std::string(reinterpret_cast<const char *>(data->glsl_version)) : "???") + "\n";

    // Запись лога
    log->log(message.c_str());
}
*/
