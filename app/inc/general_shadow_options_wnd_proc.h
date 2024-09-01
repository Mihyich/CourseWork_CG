#ifndef GENERAL_SHADOW_OPTIONS_WND_PROC_H
#define GENERAL_SHADOW_OPTIONS_WND_PROC_H

#include <Windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <string>

#include "winapi_window.h"
#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_mat_ext.h"

#include "app_args.h"

LRESULT CALLBACK GeneralShadowOptionsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // GENERAL_SHADOW_OPTIONS_WND_PROC_H