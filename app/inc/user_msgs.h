#ifndef USER_MASGS_H
#define USER_MASGS_H

// Receiver: RenderWnd
// Wparam: none
// Lparam: none
#define WM_INIT_GL_OPTIONS (WM_USER + 1)

// Receiver: RenderWnd
// Wparam: bool
// Lparam: none
#define WM_SET_WIREFRAME (WM_USER + 2)

// Receiver: RenderWnd
// Wparam: ShadowAlg
// Lparam: none
#define WM_SET_SHADOW_ALG  (WM_USER + 3)

#endif // USER_MASGS_H