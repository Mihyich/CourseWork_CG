#ifndef VAL_ARGS_H
#define VAL_ARGS_H

#include <windows.h>
#include <vector>
#include <string>

#include "Vector2D.h"

enum Formula
{
    F1,
    F2,
    F3,
    F4,
    F5,
    F6
};

namespace vals
{
    extern Formula formula;

    extern vec2 x_range;
    extern vec2 z_range;

    extern float x_step;
    extern float z_step;

    extern float x_angle;
    extern float y_angle;
    
    extern COLORREF surface_color;

    extern bool need_resolve;
}


#endif // VAL_ARGS_H