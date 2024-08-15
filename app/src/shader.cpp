#include "shader.h"

// Начальный номер созданий объектов шейдера - 1
int Shader::shader_nomer = 1;

GLint Shader::create_shader(const GLchar *source, GLint shader_type, GLuint *shader_id)
{
    // статус компиляции
    GLint compile_status;

    // шейдер не пересоздается
    if (glIsShader(*shader_id))
        return ERR_SHADER_RECREATE;

    // создать шейдер, загрузить код, скомпилировать
    *shader_id = glCreateShader(shader_type);
    glShaderSource(*shader_id, 1, &source, NULL);
    glCompileShader(*shader_id);

    // проверить статус компиляции
    glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &compile_status);

    return compile_status ? SHADER_COMPILED : ERR_SHADER_COMPILE;
}

GLboolean Shader::delete_shader(const GLuint program_id, const GLuint shader_id)
{
    GLint delete_status;

    if (!glIsShader(shader_id))
        return GL_TRUE;

    glDetachShader(program_id, shader_id);
    glDeleteShader(shader_id);

    glGetShaderiv(shader_id, GL_DELETE_STATUS, &delete_status);

    return delete_status;
}

GLint Shader::create_shader_report(const GLuint shader_id, std::string *const info)
{
    GLint result;

    // проверить, что шейдерный объект вообще создавался
    if (!glIsShader(shader_id))
    {
        info->resize(0);
        return 0;
    }
    
    // Проверить что шейдер имеет проблемы компиляции и он создан
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if (result)
    {
        info->resize(0);
        return 0;
    }

    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &result);

    if (result < 1)
        return result;

    info->resize(result);
    glGetShaderInfoLog(shader_id, result, NULL, &(*info)[0]);

    return result;
}

GLint Shader::create_program_report(const GLuint program_id, std::string *const info)
{
    GLint result;

    // проверить, что программа вообще собиралась
    if (!glIsProgram(program_id))
    {
        info->resize(0);
        return 0;
    }

    // проверить, что програма имеет ошибки собрки
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result)
    {
        info->resize(0);
        return 0;
    }

    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &result);

    if (result < 1)
        return result;

    info->resize(result);
    glGetProgramInfoLog(program_id, result, NULL, &(*info)[0]);

    return result;
}

Shader::Shader()
{
    name += std::to_string(shader_nomer);
    ++shader_nomer;
}

Shader::~Shader()
{
    delete_shader(GL_VERTEX_SHADER);
    delete_shader(GL_TESS_CONTROL_SHADER);
    delete_shader(GL_TESS_EVALUATION_SHADER);
    delete_shader(GL_GEOMETRY_SHADER);
    delete_shader(GL_FRAGMENT_SHADER);
    delete_shader(GL_COMPUTE_SHADER);
    delete_program();
}

void Shader::set_shader_name(const char *name)
{
    this->name.assign(name);
}

GLint Shader::create_from_file(const char *file_name, GLint shader_type)
{
    std::ifstream file;
    std::string source;
    std::string line;

    file.open(file_name);

    if (!file.is_open())
    {
        return ERR_SHADER_FILE_READ;
    }

    while (std::getline(file, line))
        source += line + '\n';

    return create_from_code(source.c_str(), shader_type);
}

GLint Shader::create_from_code(const GLchar *source, GLint shader_type)
{
    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        return Shader::create_shader(source, GL_VERTEX_SHADER, &vertex_shader_id);

    case GL_TESS_CONTROL_SHADER:
        return Shader::create_shader(source, GL_TESS_CONTROL_SHADER, &tess_control_shader_id);

    case GL_TESS_EVALUATION_SHADER:
        return Shader::create_shader(source, GL_TESS_EVALUATION_SHADER, &tess_evaluation_shader_id);

    case GL_GEOMETRY_SHADER:
        return Shader::create_shader(source, GL_GEOMETRY_SHADER, &geometry_shader_id);

    case GL_FRAGMENT_SHADER:
        return Shader::create_shader(source, GL_FRAGMENT_SHADER, &fragment_shader_id);

    case GL_COMPUTE_SHADER:
        return Shader::create_shader(source, GL_COMPUTE_SHADER, &compute_shader_id);

    default:
        return ERR_SHADER_TYPE;
    }
}

GLint Shader::link_program()
{
    // статус сборки программы
    GLint link_status;

    // программа не пересобирается
    if (glIsProgram(program_id))
        return ERR_PROGRAM_RECREATE;

    program_id = glCreateProgram();

    // подключить скомпилированные шейдеры
    if (glIsShader(vertex_shader_id))
        glAttachShader(program_id, vertex_shader_id);

    if (glIsShader(tess_control_shader_id))
        glAttachShader(program_id, tess_control_shader_id);

    if (glIsShader(tess_evaluation_shader_id))
        glAttachShader(program_id, tess_evaluation_shader_id);

    if (glIsShader(geometry_shader_id))
        glAttachShader(program_id, geometry_shader_id);

    if (glIsShader(fragment_shader_id))
        glAttachShader(program_id, fragment_shader_id);

    if (glIsShader(compute_shader_id))
        glAttachShader(program_id, compute_shader_id);

    // сборка программы
    glLinkProgram(program_id);

    // Удаление ненужных более шейдерный объектов
    if (!Shader::delete_shader(program_id, vertex_shader_id))
        return ERR_DELETE_SHADER;

    if (!Shader::delete_shader(program_id, tess_control_shader_id))
        return ERR_DELETE_SHADER;

    if (!Shader::delete_shader(program_id, tess_evaluation_shader_id))
        return ERR_DELETE_SHADER;

    if (!Shader::delete_shader(program_id, geometry_shader_id))
        return ERR_DELETE_SHADER;

    if (!Shader::delete_shader(program_id, fragment_shader_id))
        return ERR_DELETE_SHADER;

    if (!Shader::delete_shader(program_id, compute_shader_id))
        return ERR_DELETE_SHADER;

    // проверить статус сборки
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);

    return link_status ? PROGRAM_LINKED : ERR_PROGRAM_LINK;
}

GLboolean Shader::delete_shader(GLint shader_type)
{
    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        return Shader::delete_shader(program_id, vertex_shader_id);

    case GL_TESS_CONTROL_SHADER:
        return Shader::delete_shader(program_id, tess_control_shader_id);

    case GL_TESS_EVALUATION_SHADER:
        return Shader::delete_shader(program_id, tess_evaluation_shader_id);

    case GL_GEOMETRY_SHADER:
        return Shader::delete_shader(program_id, geometry_shader_id);

    case GL_FRAGMENT_SHADER:
        return Shader::delete_shader(program_id, fragment_shader_id);

    case GL_COMPUTE_SHADER:
        return Shader::delete_shader(program_id, compute_shader_id);

    default:
        return GL_FALSE;
    }
}

GLboolean Shader::delete_program()
{
    GLint delete_status;

    if (!glIsProgram(program_id))
        return GL_TRUE;

    glDeleteProgram(program_id);

    glGetProgramiv(program_id, GL_DELETE_STATUS, &delete_status);

    return delete_status;
}

GLvoid Shader::report(GLubyte type)
{
    std::string info;
    std::string message;

    if ((type & REPORT_VS) == REPORT_VS &&
        Shader::create_shader_report(vertex_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_TCS) == REPORT_TCS &&
        Shader::create_shader_report(tess_control_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_TES) == REPORT_TES &&
        Shader::create_shader_report(tess_evaluation_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_GS) == REPORT_GS &&
        Shader::create_shader_report(geometry_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_FS) == REPORT_FS &&
        Shader::create_shader_report(fragment_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_CS) == REPORT_CS &&
        Shader::create_shader_report(compute_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_PROG) == REPORT_PROG &&
        Shader::create_program_report(program_id, &info))
    {
        message += info;
    }

    if (!message.size())
        return;

    std::cout << message.c_str();
}

GLvoid Shader::report(const wchar_t *const wfile_name, GLubyte type)
{
    char *file_name = NULL;
    
    wchar_to_char(wfile_name, &file_name);

    report(file_name, type);

    delete[] file_name;
}

GLvoid Shader::report(const char *const file_name, GLubyte type)
{
    std::ofstream file;
    std::string info;
    std::string message;

    if ((type & REPORT_VS) == REPORT_VS &&
        Shader::create_shader_report(vertex_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_TCS) == REPORT_TCS &&
        Shader::create_shader_report(tess_control_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_TES) == REPORT_TES &&
        Shader::create_shader_report(tess_evaluation_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_GS) == REPORT_GS &&
        Shader::create_shader_report(geometry_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_FS) == REPORT_FS &&
        Shader::create_shader_report(fragment_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_CS) == REPORT_CS &&
        Shader::create_shader_report(compute_shader_id, &info))
    {
        message += info;
    }

    if ((type & REPORT_PROG) == REPORT_PROG &&
        Shader::create_program_report(program_id, &info))
    {
        message += info;
    }

    if (!message.size())
        return;

    // запись
    file.open(file_name, std::ios_base::app);

    if (!file.is_open())
        return;

    file << message.c_str();
    file.close();
}

GLvoid Shader::use(void) const
{
    glUseProgram(program_id);
}

GLvoid Shader::init_uniforms(void)
{       
    GLint uniform_count; // Количество униформ
    GLint uniform_max_length; // Максимальная длина имени униформы
    GLchar *uniform_name; // Имя униформы
    GLint location; // Расположение униформы

    glUseProgram(program_id);

    glGetProgramiv(program_id, GL_ACTIVE_UNIFORMS, &uniform_count);
    if (!uniform_count) return;

    glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniform_max_length);
    if (!uniform_max_length) return;

    uniform_name = new GLchar[uniform_max_length];
    uniforms.clear();

    for (GLint i = 0; i < uniform_count; ++i)
    {
        glGetProgramResourceName(program_id, GL_UNIFORM, i, uniform_max_length, nullptr, uniform_name);
        location = glGetUniformLocation(program_id, uniform_name);
        // printf("Uniform #%d: Name: %s, Location: %d\n", i, uniform_name, location);
        uniforms[uniform_name] = location;
    }

    glUseProgram(0);
    delete[] uniform_name;
}

GLvoid Shader::init_attribs(void)
{
    GLint attrib_count; // Количество атрибутов
    GLint attrib_max_length; // Максимальная длина имени атрибута
    GLchar *attrib_name = nullptr;
    GLint temp_int;
    GLenum temp_enum;
    GLint attrib_location;

    glUseProgram(program_id);

    glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTES, &attrib_count);
    if (!attrib_count) return;

    glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attrib_max_length);
    if (!attrib_max_length) return;

    attrib_name = new GLchar[attrib_max_length];
    attribs.clear();

    for (GLint i = 0; i < attrib_count; ++i)
    {
        glGetActiveAttrib(program_id, i, attrib_max_length, nullptr, &temp_int, &temp_enum, attrib_name);
        attrib_location = glGetAttribLocation(program_id, attrib_name);
        // printf("Attribute #%d: Name: %s, Location: %d\n", i, attrib_name, attrib_location);
        attribs[attrib_name] = attrib_location;
    }

    glUseProgram(0);
    delete[] attrib_name;
}

GLvoid Shader::init_uniforms_and_attribs(void)
{
    init_uniforms();
    init_attribs();
}

GLvoid Shader::print_uniforms(bool extra_info) const
{
    int index = 0;
    shader_linker::const_iterator it = uniforms.begin();

    printf("%s - uniforms, count = %zu:\n", &name[0], uniforms.size());

    if (extra_info)
    {
        glUseProgram(program_id);

        GLenum props[13] = 
        {
            GL_NAME_LENGTH, GL_TYPE, GL_ARRAY_SIZE, GL_LOCATION,
            GL_BLOCK_INDEX, GL_IS_ROW_MAJOR, GL_ATOMIC_COUNTER_BUFFER_INDEX,
            GL_REFERENCED_BY_VERTEX_SHADER, GL_REFERENCED_BY_TESS_CONTROL_SHADER,
            GL_REFERENCED_BY_TESS_EVALUATION_SHADER, GL_REFERENCED_BY_GEOMETRY_SHADER,
            GL_REFERENCED_BY_FRAGMENT_SHADER, GL_REFERENCED_BY_COMPUTE_SHADER
        };

        GLint params[13];
        
        for (; it != uniforms.end(); ++it)
        {
            glGetProgramResourceiv(program_id, GL_UNIFORM, index, 13, props, 13, nullptr, params);

            printf("\n\t#%d: uniform from \"%s\"\n", index++, &name[0]);
            printf("\t{\n");
            printf("\t\tGL_NAME:        \"%s\"\n", &it->first[0]);
            printf("\t\tGL_NAME_LENGTH: %d\n", params[0]);
            printf("\t\tGL_TYPE:        0x%x\n", params[1]);
            printf("\t\tGL_ARRAY_SIZE:  %d\n", params[2]);
            printf("\t\tGL_LOCATION:    %d\n", params[3]);
            printf("\t\tGL_BLOCK_INDEX: %d\n", params[4]);
            printf("\t\tGL_IS_ROW_MAJOR: %d\n", params[5]);
            printf("\t\tGL_ATOMIC_COUNTER_BUFFER_INDEX: %d\n", params[6]);
            printf("\t\tGL_REFERENCED_BY_VERTEX_SHADER:          %d\n", params[7]);
            printf("\t\tGL_REFERENCED_BY_TESS_CONTROL_SHADER:    %d\n", params[8]);
            printf("\t\tGL_REFERENCED_BY_TESS_EVALUATION_SHADER: %d\n", params[9]);
            printf("\t\tGL_REFERENCED_BY_GEOMETRY_SHADER:        %d\n", params[10]);
            printf("\t\tGL_REFERENCED_BY_FRAGMENT_SHADER:        %d\n", params[11]);
            printf("\t\tGL_REFERENCED_BY_COMPUTE_SHADER:         %d\n", params[12]);
            printf("\t}\n");
        }

        glUseProgram(0);
    }
    else
        for (; it != uniforms.end(); ++it)
            printf("\t#%d: Name: \"%s\", Location: %d\n", index++, &it->first[0], it->second);

    std::cout << '\n';
}

GLvoid Shader::print_attribs(bool extra_info) const
{
    size_t index = 0;
    shader_linker::const_iterator it = attribs.begin();

    printf("%s - Attrbis, count = %zu:\n", &name[0], attribs.size());

    if (extra_info && attribs.size())
    {
        glUseProgram(program_id);

        GLint attrib_max_length;
        GLint size;
        GLenum type;
        GLchar *attrib_name = nullptr;
        GLint attrib_location;

        glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attrib_max_length);
        if (!attrib_max_length) return;

        attrib_name = new GLchar[attrib_max_length];

        for (; index < attribs.size(); ++index)
        {
            glGetActiveAttrib(program_id, index, attrib_max_length, nullptr, &size, &type, attrib_name);
            attrib_location = glGetAttribLocation(program_id, attrib_name);

            printf("\n\t#%lld: attribute from \"%s\"\n", index, &name[0]);
            printf("\t{\n");
            printf("\t\tName: \"%s\"\n", attrib_name);
            printf("\t\tSize: %d\n", size);
            printf("\t\tType: %u\n", type);
            printf("\t\tLocation: %d\n", attrib_location);
            printf("\t}\n");
        }

        delete[] attrib_name;
        glUseProgram(0);
    }
    else
        for (; it != attribs.end(); ++it)
            printf("\t#%lld: Name: \"%s\", Location: %d\n", index++, &it->first[0], it->second);

    std::cout << '\n';
}

GLvoid Shader::print_uniforms_and_attribs(bool uniform_extra_info, bool attribs_extra_info) const
{
    print_uniforms(uniform_extra_info);
    print_attribs(attribs_extra_info);
}

GLint Shader::find_uniform_location(const GLchar *name) const
{
    return glGetUniformLocation(program_id, name);
}

GLint Shader::find_attrib_location(const GLchar *name) const
{
    return glGetAttribLocation(program_id, name);
}

GLint Shader::get_uniform_location(const GLchar *name) const
{
    shader_linker::const_iterator it = uniforms.find(name);
    return it != uniforms.end() ? it->second : SHADER_LOCATION_NOT_FOUNDED;
}

GLint Shader::get_attrib_location(const GLchar *name) const
{
    shader_linker::const_iterator it = attribs.find(name);
    return it != uniforms.end() ? it->second : SHADER_LOCATION_NOT_FOUNDED;
}

const char *Shader::get_name(void) const
{
    return &name[0];
}
