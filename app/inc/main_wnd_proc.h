#ifndef MAIN_WND_PROC_H
#define MAIN_WND_PROC_H

#include <Windows.h>
#include "winapi_window.h"
#include "toolbar_wnd_proc.h"
#include "drawarea_wnd_poc.h"
#include "drawareainfo_wnd_poc.h"
#include "resource.h"
#include "app_args.h"
#include "user_msgs.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // MAIN_WND_PROC_H