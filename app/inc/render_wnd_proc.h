#ifndef RENDER_WND_PROC_H
#define RENDER_WND_PROC_H

#include <windows.h>
#include <math.h>


#include "shader.h"
#include "shader_extensions.h"


#include "Vector3D.h"
#include "Matrix4D.h"
#include "Quaternion.h"


#include "winapi_GLextensions.h"
#include "winapi_mat_ext.h"
#include "winapi_char_converter.h"


#include "ModelLoader.h"
#include "PlaneMeshGenerator.h"


#include "LightStruct.h"
#include "Light.h"


#include "RayTraceBvhStruct.h"
#include "RayTraceTrianglesGenerator.h"
#include "RayTraceBvhGenerator.h"
#include "RayTraceBufferGenerator.h"
#include "RayTraceTextureGenerator.h"


#include "DepthBufferGenerator.h"
#include "DepthBufferExpGenerator.h"


#include "ShadowAlgEnum.h"


#include "ShadowMapRenderData.h"
#include "ShadowMap.h"
#include "ShadowMapPcf.h"
#include "ShadowMapNoise.h"
#include "ShadowMapPcss.h"
#include "ShadowMapPcssNoise.h"
#include "ShadowMapEsm.h"
#include "ShadowMapVsm.h"


#include "RayTracingRenderData.h"
#include "RayTracingDebug.h"
#include "RayTracingHard.h"
#include "RayTracingSoft.h"


#include "app_args.h"
#include "ResolutionMapLimit.h"
#include "user_msgs.h"

enum CameraMode
{
    ORBITTING = 0,
    MOVING
};

LRESULT CALLBACK RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // RENDER_WND_PROC_H