#include "app_args.h"

namespace app
{
    HINSTANCE hInst = nullptr;
    PSTR lpCmdLine = nullptr;
    
    WinApiWindow MainWnd;
    const POINT MinMainWndSize = { 400,  300};
    
    WinApiWindow ToolbarWnd;
    LONG ToolbarWidth = 200;

    WinApiGLWindow RenderWnd;

    WinApiFont Fonts;
}