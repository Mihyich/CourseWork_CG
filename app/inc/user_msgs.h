#ifndef USER_MASGS_H
#define USER_MASGS_H

// Receiver: RenderWnd
// Wparam: none
// Lparam: none
#define WM_INIT_GL_OPTIONS (WM_USER + 1)

// Receiver: RenderWnd
// Wparam: WCHAR* - путь к файлу
// Lparam: BOOL - инвертирование порядка вершин
#define WM_LOAD_MODEL (WM_USER + 2)

// Receiver: RenderWnd
// Wparam: bool
// Lparam: none
#define WM_SET_WIREFRAME (WM_USER + 3)

// Receiver: RenderWnd
// Wparam: ShadowAlg
// Lparam: none
#define WM_SET_SHADOW_ALG  (WM_USER + 4)

// Receiver: RenderWnd
// Wparam: cpvec3
// Lparam: none
#define WM_SET_LIGHT_POSITION (WM_USER + 5)

// Receiver: RenderWnd
// Wparam: cpvec3
// Lparam: none
#define WM_SET_LIGHT_DIRECTION (WM_USER + 6)

// Receiver: RenderWnd
// Wparam: cpvec3
// Lparam: none
#define WM_SET_LIGHT_COLOR (WM_USER + 7)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_LIGHT_RADIUS (WM_USER + 8)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_LIGHT_INTENSITY (WM_USER + 9)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_LIGHT_INNER_CUTOFF (WM_USER + 10)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_LIGHT_OUTER_CUTOFF (WM_USER + 11)

// Receiver: RenderWnd
// Wparam: const int*
// Lparam: none
#define WM_SET_LIGHT_TYPE (WM_USER + 12)

// Настроки ShadowMap ===================================================================

// Receiver: RenderWnd
// Wparam: const int*
// Lparam: none
#define WM_SET_SHADOWMAP_ALGORITM (WM_USER + 13)

// Receiver: RenderWnd
// Wparam: const int*
// Lparam: const int*
#define WM_SET_SHADOWMAP_RESOLUTION (WM_USER + 14)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_SHADOWMAP_BIAS (WM_USER + 15)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_SHADOWMAP_PCF_RADIUS (WM_USER + 16)

// Receiver: RenderWnd
// Wparam: const float*
// Lparam: none
#define WM_SET_SHADOWMAP_EXP_K (WM_USER + 17)

// Receiver: RenderWnd
// Wparam: const int*
// Lparam: none
#define WM_SET_SHADOWMAP_RENDER_MODE (WM_USER + 18)

// Общие настройки теней ================================================================

#endif // USER_MASGS_H