#ifndef ALG_H
#define ALG_H

#include <windows.h>
#include <vector>
#include <unordered_set>
#include <limits>
#include <algorithm>

#include "winapi_render.h"
#include "winapi_frame_buffer.h"
#include "winapi_bitmap_saver.h"

#include "Vector2D.h"
#include "app_args.h"
#include "val_args.h"

struct Segment
{
    vec2 sp;
    vec2 ep;
};

void drawSurface(const WinApiRender &Render, cpvec2 x_range, cpvec2 z_range, float x_step, float z_step, Formula formula, COLORREF color);

#endif // ALG_H