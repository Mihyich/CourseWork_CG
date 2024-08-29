#ifndef PATHTRACING_WND_PROC_H
#define PATHTRACING_WND_PROC_H

#include <Windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <string>

#include "winapi_window.h"
#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_mat_ext.h"

#include "app_args.h"

LRESULT CALLBACK PathTracingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // PATHTRACING_WND_PROC_H