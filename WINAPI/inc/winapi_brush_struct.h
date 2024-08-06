#ifndef WINAPI_BRUSH_STRUCT_H
#define WINAPI_BRUSH_STRUCT_H

#include <windows.h>

typedef struct WinApiBrushSolidStruct WinApiBrushSolidStruct;
typedef WinApiBrushSolidStruct *WinApiBrushSolidStruct_p;

typedef struct WinApiBrushHatchStruct WinApiBrushHatchStruct;
typedef WinApiBrushHatchStruct *WinApiBrushHatchStruct_p;

typedef struct WinApiBrushPatternStruct WinApiBrushPatternStruct;
typedef WinApiBrushPatternStruct *WinApiBrushPatternStruct_p;

typedef union WinApiBrushUnion WinApiBrushUnion;
typedef WinApiBrushUnion *WinApiBrushUnion_p;

typedef struct WinApiBrushStruct WinApiBrushStruct;
typedef WinApiBrushStruct *WinApiBrushStruct_p;

enum WinApiBrushType
{
    BRUSH_TYPE_UNDEF = 0,
    BRUSH_TYPE_SOLID,
    BRUSH_TYPE_HATCH,
    BRUSH_TYPE_PATTERN
};

struct WinApiBrushSolidStruct
{
    COLORREF color;
};

struct WinApiBrushHatchStruct
{
    int iHatch;
    COLORREF color;
};

struct WinApiBrushPatternStruct
{
    HBITMAP hbm;
};

union WinApiBrushUnion
{
    WinApiBrushSolidStruct Solid;
    WinApiBrushHatchStruct Hatch;
    WinApiBrushPatternStruct Pattern;
};

struct WinApiBrushStruct
{
    WinApiBrushUnion brush;
    WinApiBrushType type;
};

#endif // WINAPI_BRUSH_STRUCT_H