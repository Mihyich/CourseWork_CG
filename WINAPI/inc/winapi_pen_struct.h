#ifndef WINAPI_PEN_STRUCT_H
#define WINAPI_PEN_STRUCT_H

#include <windows.h>

typedef struct WinApiPenStruct WinApiPenStruct;
typedef WinApiPenStruct *WinApiPenStruct_p;

struct WinApiPenStruct
{
  int iStyle;
  int cWidth;
  COLORREF color;
};

#endif // WINAPI_PEN_STRUCT_H