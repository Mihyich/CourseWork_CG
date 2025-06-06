#ifndef SHADOWMAP_WND_PROC_H
#define SHADOWMAP_WND_PROC_H

#include <Windows.h>
#include <CommCtrl.h> // для общих элементов управления окна
#include <string>

#include "winapi_window.h"
#include "winapi_common.h"
#include "winapi_font_common.h"
#include "winapi_mat_ext.h"

#include "general_shadow_options_wnd_proc.h"

#include "app_args.h"
#include "ShadowAlgEnum.h"
#include "ResolutionMapLimit.h"
#include "user_msgs.h"

LRESULT CALLBACK ShadowMapWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // SHADOWMAP_WND_PROC_H