#ifndef RENDER_WND_PROC_H
#define RENDER_WND_PROC_H

#include <windows.h>
#include <math.h>

#include "shader.h"

#include "Vector3D.h"
#include "Matrix4D.h"

#include "winapi_GLextensions.h"
#include "winapi_mat_ext.h"

#include "app_args.h"
#include "user_msgs.h"

LRESULT CALLBACK RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // RENDER_WND_PROC_H