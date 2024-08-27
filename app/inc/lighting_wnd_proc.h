#ifndef LIGHTING_WND_PROC_H
#define LIGHTING_WND_PROC_H

#include <windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <richedit.h>

#include "LightStruct.h"

#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_brush.h"
#include "winapi_choose_color_dialog.h"
#include "winapi_mat_ext.h"

#include "app_args.h"

LRESULT CALLBACK LightingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // LIGHTING_WND_PROC_H