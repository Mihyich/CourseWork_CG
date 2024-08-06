#ifndef INPUT_DRAWER_H
#define INPUT_DRAWER_H

#include <vector>
#include "Vector2D.h"
#include "winapi_render.h"
#include "winapi_color_common.h"

void draw_clipper(const WinApiRender &Render, const std::vector<vec2> &points, COLORREF color, int line_width = 1);

void draw_segments(const WinApiRender &Render, const std::vector<vec2> &points, COLORREF color, int line_width = 1);

#endif // INPUT_DRAWER_H