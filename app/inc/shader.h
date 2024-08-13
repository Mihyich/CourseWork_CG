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

class shader
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

    /// @brief Создать шейдер по предоставленному коду
    /// @param source Код шейдера в фомате utf-8
    /// @param shader_type Тип шейдера, который должен быть гарантированно корректным
    /// @param shader_id Айди созданного шейдера
    /// @return Коды возврата
    GLint create_shader(const GLchar *source, GLint shader_type, GLuint *shader_id);

    /// @brief Удаление шейдера
    /// @param program_id Айди програмы, к которой прикреплен шейдер
    /// @param shader_id Айди удаляемого шейдера
    /// @return Флаг удаления: GL_TRUE/GL_FALSE
    static GLboolean delete_shader(const GLuint program_id, const GLuint shader_id);

    /// @brief Получить текстовую информацию о шейдере
    /// @param shader_id Айди шейдера
    /// @param info указатель на тектовую информацию
    /// @return Длина текстовой информации
    static GLint create_shader_report(const GLuint shader_id, std::string *const info);

    /// @brief Получить текстовую информацию о шейдерной программе
    /// @param program_id Айди шейлерной программы
    /// @param info указатель на тектовую информацию
    /// @return Длина текстовой информации
    static GLint create_program_report(const GLuint program_id, std::string *const info);

public:
    shader();
    ~shader();

    /// @brief Присвоить шейдерной программе имя
    /// Упрощает чтение отладочной информации
    /// @param name
    void set_shader_name(const char *name);

    /// @brief Скомпилировать шейдер опр. типа по исходному коду из текстового файла
    /// @param file_name Путь к файлу с исходным кодом шейдера в utf-8
    /// @param shader_type Тип шейдера
    /// @return Коды возврата
    GLint create_from_file(const char *file_name, GLint shader_type);

    /// @brief Скомпилировать шейдер опр. типа по исходному коду
    /// @param source Исходный код в utf-8 формате
    /// @param shader_type Тип шейдера
    /// @return Коды возврата
    GLint create_from_code(const GLchar *source, GLint shader_type);

    /// @brief Сборка программы из созданных и скомпилированных шейдеров.
    /// В сборке учавствуют все успешно скомпилированные шейдеры
    /// Гарантируется удалание шейдерных объектов после завершения
    /// процесса сборки шейдеров.
    /// @return Коды возврата
    GLint link_program();

    /// @brief Удаление шейдера
    /// @param shader_type Тип шейдера
    /// @return Флаг удаления: GL_TRUE/GL_FALSE
    GLboolean delete_shader(GLint shader_type);

    /// @brief Удаление шейдерной программы
    /// @return Флаг удаления: GL_TRUE/GL_FALSE
    GLboolean delete_program();

    /// @brief Вывести информацию о определенных шейдерах и/или программе
    /// в консоль
    /// @param file_name Путь к файлу для записи
    /// @param type Какой отчет делать. Активировать соответстующие биты
    /// с помощью REPORT_VS, REPORT_TCS, REPORT_TES, REPORT_GS, REPORT_FS,
    /// REPORT_CS, REPORT_PROG.
    GLvoid report(GLubyte type);

    /// @brief Вывести информацию о определенных шейдерах и/или программе
    /// в файл
    /// @param file_name Путь к файлу для записи
    /// @param type Какой отчет делать. Активировать соответстующие биты
    /// с помощью REPORT_VS, REPORT_TCS, REPORT_TES, REPORT_GS, REPORT_FS,
    /// REPORT_CS, REPORT_PROG.
    GLvoid report(const wchar_t *const wfile_name, GLubyte type);

    /// @brief Вывести информацию о определенных шейдерах и/или программе
    /// в файл
    /// @param file_name Путь к файлу для записи
    /// @param type Какой отчет делать. Активировать соответстующие биты
    /// с помощью REPORT_VS, REPORT_TCS, REPORT_TES, REPORT_GS, REPORT_FS,
    /// REPORT_CS, REPORT_PROG.
    GLvoid report(const char *const file_name, GLubyte type);

    /// @brief Активировать шейдерную программу
    GLvoid use(void) const;

    /// @brief Инициализировать данные о униформах
    GLvoid init_uniforms(void);

    /// @brief Инициализировать данные о атрибутах
    GLvoid init_attribs(void);

    /// @brief Инициализировать данные о униформах и атрибутах
    GLvoid init_attribs_and_uniforms(void);

    /// @breif Вывод униформ из словаря
    /// @param extra_info - Нужно ли выводить дополнительную информацию
    GLvoid print_uniforms(bool extra_info = false) const;

    /// @breif Вывод атрибут
    /// @param extra_info - Нужно ли выводить дополнительную информацию
    GLvoid print_attribs(bool extra_info = false) const;

    /// @brief Получить расположение униформы по ее названию в шейдере
    /// @param name - Название униформы
    /// @return Расположение униформы
    GLint find_uniform_location(const GLchar *name) const;

    /// @brief Получить расположение атрибута по его названию в шейдере
    /// @param name - Название атрибута
    /// @return Расположение атрибута
    GLint find_attrib_location(const GLchar *name) const;

    /// @brief Получить расположение униформы по ее названию из созданного
    /// словаря для униформ
    /// @param name - Название униформы
    /// @return Расположение униформы
    GLint get_uniform_location(const GLchar *name) const;

    /// @brief Получить расположение атрибута по его названию из созданного
    /// словаря для атрибутов
    /// @param name - Название атрибута
    /// @return Расположение атрибута
    GLint get_attrib_location(const GLchar *name) const;

    /// @brief Получить имя шейдера
    /// @return Указатель на имя
    const char *get_name(void) const;
};

#endif // SHADER_H