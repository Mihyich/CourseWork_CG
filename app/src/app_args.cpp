#include "app_args.h"

namespace app
{
    HINSTANCE hInst = nullptr;
    PSTR lpCmdLine = nullptr;
    
    WinApiWindow MainWnd;
    const POINT MinMainWndSize = { 400,  300};
    
    WinApiWindow ToolbarWnd;
    LONG ToolbarMinWidth = 100;
    LONG ToolbarWidth = 200;

    WinApiWindow ShadowWnd;
    WinApiWindow ShadowMapWnd;
    WinApiWindow RayTracingWnd;
    WinApiWindow PathTracingWnd;

    WinApiWindow GeneralShadowOptionsWnd;

    WinApiWindow LightingWnd;

    WinApiWindow ModelWnd;

    WinApiGLWindow RenderWnd;

    WinApiFont Fonts;
}