#ifndef SHADOW_WND_PROC_H
#define SHADOW_WND_PROC_H

#include <Windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <string>

#include "winapi_window.h"
#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_mat_ext.h"

#include "shadowMap_wnd_proc.h"
#include "rayTracing_wnd_proc.h"
#include "pathTracing_wnd_proc.h"

#include "app_args.h"

LRESULT CALLBACK ShadowWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // SHADOW_WND_PROC_H