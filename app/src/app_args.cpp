#include "app_args.h"

namespace app
{
    HINSTANCE hInst = nullptr;
    PSTR lpCmdLine = nullptr;
    
    WinApiWindow MainWnd;
    const POINT MinMainWndSize = { 400,  300};
    
    WinApiWindow ToolbarWnd;
    const LONG ToolbarWidth = 100;

    WinApiGLWindow RenderWnd;

    WinApiFont Fonts;
}