#include "val_args.h"

namespace vals
{
    Formula formula = F1;

    vec2 x_range = {0.f, 0.f};
    vec2 z_range = {0.f, 0.f};

    float x_step = 0.f;
    float z_step = 0.f;

    float x_angle = 30.f;
    float y_angle = 30.f;

    COLORREF surface_color = RGB(0, 0, 255);

    bool need_resolve = false;
}