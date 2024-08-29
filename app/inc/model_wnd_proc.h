#ifndef MODEL_WND_PROC_H
#define MODEL_WND_PROC_H

#include <Windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <string>

#include "winapi_window.h"
#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_mat_ext.h"

#include "shadow_wnd_proc.h"
#include "lighting_wnd_proc.h"

#include "app_args.h"

LRESULT CALLBACK ModelWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // MODEL_WND_PROC_H