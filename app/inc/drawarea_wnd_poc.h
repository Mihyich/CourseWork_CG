#ifndef DRAWAREA_WND_PROC
#define DRAWAREA_WND_PROC

#include <Windows.h>
#include <cstdio>
#include <string>
#include <vector>

#include "resource.h"
#include "app_args.h"
#include "val_args.h"
#include "LA_sup.h"
#include "Vector2D.h"

#include "winapi_mouse.h"
#include "winapi_render.h"
#include "winapi_common.h"
#include "toolbar_wnd_proc.h"

#include "input_drawer.h"
#include "alg.h"

#include "user_msgs.h"

LRESULT CALLBACK DrawAreaWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // DRAWAREA_WND_PROC