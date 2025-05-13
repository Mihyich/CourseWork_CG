#include "winapi_mat_ext.h"

size_t get_digit_count_in_number(int val)
{
    return val ? (int)floor(log10(abs(val))) + 1 : 1;
}

size_t get_char_count_in_number(int val)
{
    size_t count = get_digit_count_in_number(val);
    
    if (val < 0)
    {
        ++count;
    }
    
    return count;
}

LONG get_rect_width(const RECT &rect)
{
    return rect.right - rect.left;
}

LONG get_rect_height(const RECT &rect)
{
    return rect.bottom - rect.top;
}

void get_rect_center(const RECT &rect, POINT &center)
{
    center.x = (LONG)roundf(WA_INTERPOLATE(rect.left, rect.right, 0.5f));
    center.y = (LONG)roundf(WA_INTERPOLATE(rect.top, rect.bottom, 0.5f));
}