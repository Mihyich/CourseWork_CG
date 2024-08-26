#ifndef TOOLBAR_WND_PROC_H
#define TOOLBAR_WND_PROC_H

#include <Windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <string>

#include "winapi_window.h"
#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_mat_ext.h"

#include "lighting_wnd_proc.h"

#include "app_args.h"

#define IDB_SURFACE_FUNC 1

#define IDB_X_LIMIT 2
#define IDB_Z_LIMIT 3

#define IDB_X_STEP 4
#define IDB_Z_STEP 5

#define IDB_CHOOSE_SURFACE_COLOR 6
#define IDB_SURFACE_LAUNCH 7

LRESULT CALLBACK ToolbarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // TOOLBAR_WND_PROC_H