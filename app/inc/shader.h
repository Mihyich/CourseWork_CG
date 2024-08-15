#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "winapi_GLextensions.h"
#include "winapi_char_converter.h"

#define SHADER_COMPILED      0 // шейдер успешно создан
#define ERR_SHADER_FILE_READ 1 // проблема чтения файла
#define ERR_SHADER_TYPE      2 // неизвестный тип шейдера
#define ERR_SHADER_RECREATE  3 // попытка пересоздания созданного шейдера
#define ERR_SHADER_COMPILE   4 // шейдер создался, но не скомпилировался
#define ERR_DELETE_SHADER    5 // ошибка при попытке удаления шейдера

#define PROGRAM_LINKED       0 // шейдерная программа собрана
#define ERR_PROGRAM_RECREATE 6 // попытка пересоздания созданной шейрерной программы
#define ERR_PROGRAM_LINK     7 // программа создана, но с ошибками сборки
#define ERR_DELETE_PROGRAM   8 // ошибак при попытке удаления собранной шейдреной программы

#define REPORT_VS   0b0000001 // бит вершинного шейдера
#define REPORT_TCS  0b0000010 // бит тес. контрольного шейдера
#define REPORT_TES  0b0000100 // бит тес. оценочного шейдера
#define REPORT_GS   0b0001000 // бит геометрического шейдера
#define REPORT_FS   0b0010000 // бит фрагментного шейдера
#define REPORT_CS   0b0100000 // бит вычислительного шейдера
#define REPORT_PROG 0b1000000 // бит шейдерной программы

// Код возврата при не найденой позиции униформы
#define SHADER_LOCATION_NOT_FOUNDED INT_MIN

// Связь данных о униформе/атрибуте через их имя
typedef std::map<std::string, GLint> shader_linker;

class Shader
{
private:
    // айди шейдера
    GLuint program_id = 0;
    // айди шейдерных програм
    GLuint vertex_shader_id = 0;          // Вершинный шейдер
    GLuint tess_control_shader_id = 0;    // Тесселяционный контрольный шейдер
    GLuint tess_evaluation_shader_id = 0; // Тесселяционный оценочный шейдер
    GLuint geometry_shader_id = 0;        // Геометрический шейдер
    GLuint fragment_shader_id = 0;        // Фрагментный шейдер
    GLuint compute_shader_id = 0;         // Вычислительный шейдер

    GLubyte file_err_read_bits = 0; // Биты для проваленных попыток чтения файла

    static int shader_nomer; // Номер создания объекта шейдера
    std::string name = "noname_shader"; // Название шейдера, для более удобной отладки

    shader_linker uniforms; // словарь униформ
    shader_linker attribs;  // словарь атрибутов

    std::map<std::string, GLint> unifs;

    GLint create_shader(const GLchar *source, GLint shader_type, GLuint *shader_id);

    static GLboolean delete_shader(const GLuint program_id, const GLuint shader_id);

    static GLint create_shader_report(const GLuint shader_id, std::string *const info);

    static GLint create_program_report(const GLuint program_id, std::string *const info);

public:
    Shader();
    ~Shader();

    void set_shader_name(const char *name);

    GLint create_from_file(const char *file_name, GLint shader_type);

    GLint create_from_code(const GLchar *source, GLint shader_type);

    GLint link_program();

    GLboolean delete_shader(GLint shader_type);

    GLboolean delete_program();

    GLvoid report(GLubyte type);

    GLvoid report(const wchar_t *const wfile_name, GLubyte type);

    GLvoid report(const char *const file_name, GLubyte type);

    GLvoid use(void) const;

    GLvoid init_uniforms(void);

    GLvoid init_attribs(void);

    GLvoid init_uniforms_and_attribs(void);

    GLvoid print_uniforms(bool extra_info = false) const;

    GLvoid print_attribs(bool extra_info = false) const;

    GLvoid print_uniforms_and_attribs(bool uniform_extra_info = false, bool attribs_extra_info = false) const;

    GLint find_uniform_location(const GLchar *name) const;

    GLint find_attrib_location(const GLchar *name) const;

    GLint get_uniform_location(const GLchar *name) const;

    GLint get_attrib_location(const GLchar *name) const;

    const char *get_name(void) const;
};

#endif // SHADER_H