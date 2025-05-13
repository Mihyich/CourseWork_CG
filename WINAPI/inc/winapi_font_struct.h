#ifndef WINAPI_FONT_STRUCT_H
#define WINAPI_FONT_STRUCT_H

#include <windows.h>

typedef struct FontParam *FontParam_t;
typedef const FontParam_t FontParam_ct;

// высота в пикселях = высота в пунктах * разрешение экрана в dpi
//                                        -----------------------
//                                                  72

// Параметры шрифта
struct FontParam
{
    int cHeight; // Высота символов в пунктах
    int cWidth; // Ширина символов в пунктах
    int cEscapement; // Угол, между вектором базовой линии и линией символов в десятых градуса
    int cOrientation; // Угол, между осью X устройства и осью X базового шрифта
    int cWeight; // толщина: FW_DONTCARE, FW_THIN, FW_NORMAL, FW_BOLD, и т. д.
    DWORD bItalic; // Флаг, указывающий, является ли шрифт курсивным (наклонным)
    DWORD bUnderline; // Флаг, указывающий, подчеркнут ли шрифт
    DWORD bStrikeOut; // Флаг, указывающий, зачеркнут ли шрифт
    DWORD iCharSet; // Набор символов: кириллица, латиница и т. д.
    DWORD iOutPrecision; // Точность вывода символов
    DWORD iClipPrecision; // Точность отсечения символов
    DWORD iQuality; // Качество шрифта
    DWORD iPitchAndFamily; // Семейство и ширина шрифта: моноширинный или переменной ширины
    LPCWSTR pszFaceName; // Указатель на строку с именем шрифта
};

#endif // WINAPI_FONT_STRUCT_H