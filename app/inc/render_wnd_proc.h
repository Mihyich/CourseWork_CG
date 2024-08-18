#ifndef RENDER_WND_PROC_H
#define RENDER_WND_PROC_H

#include <windows.h>
#include <math.h>

#include "shader.h"
#include "shader_extensions.h"

#include "Vector3D.h"
#include "Matrix4D.h"
#include "Quaternion.h"

#include "ModelLoader.h"

#include "DepthBufferGenerator.h"

#include "winapi_GLextensions.h"
#include "winapi_mat_ext.h"
#include "winapi_char_converter.h"

#include "ShadowAlgEnum.h"
#include "ShadowMapOrthogonal.h"
#include "ShadowMapPerspective.h"

#include "app_args.h"
#include "user_msgs.h"

enum CameraMode
{
    ORBITTING = 0,
    MOVING
};

LRESULT CALLBACK RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // RENDER_WND_PROC_H