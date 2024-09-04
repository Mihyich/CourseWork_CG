#ifndef MAIN_WND_PROC_H
#define MAIN_WND_PROC_H

#include <Windows.h>

#include "winapi_window.h"

#include "ModelLoaderDialogProc.h"

#include "toolbar_wnd_proc.h"
#include "render_wnd_proc.h"

#include "resource.h"
#include "user_msgs.h"
#include "app_args.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // MAIN_WND_PROC_H