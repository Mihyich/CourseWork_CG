#ifndef DRAWAERAINFO_WND_PROC_H
#define DRAWAERAINFO_WND_PROC_H

#include <windows.h>
#include "app_args.h"

void repos_child_wnds_in_drawareainfo_wnd(void);

LRESULT CALLBACK DrawAreaInfoWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // DRAWAERAINFO_WND_PROC_H