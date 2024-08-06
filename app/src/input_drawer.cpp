#include "input_drawer.h"

void draw_clipper(const WinApiRender &Render, const std::vector<vec2> &points, COLORREF color, int line_width)
{
    if (!points.size())
        return;

    WinApiPen Pen(Render.get_hdc());
    std::vector<POINT> client_points(points.size(), {0, 0});
    size_t i = 0;

    for (vec2 p : points)
    {
        Render.convert_from_client_into_local(&p);
        client_points[i] = { (LONG)roundf(p.x), (LONG)roundf(p.y) };
        ++i;
    }

    Pen.select(PS_SOLID, line_width, color);
    Render.draw_line_strip(client_points.data(), client_points.size());
}

void draw_segments(const WinApiRender &Render, const std::vector<vec2> &points, COLORREF color, int line_width)
{
    if (!points.size())
        return;

    WinApiPen Pen(Render.get_hdc());
    std::vector<POINT> client_points(points.size(), {0, 0});
    size_t i = 0;

    for (vec2 p : points)
    {
        Render.convert_from_client_into_local(&p);
        client_points[i] = { (LONG)roundf(p.x), (LONG)roundf(p.y) };
        ++i;
    }

    Pen.select(PS_SOLID, line_width, color);
    Render.draw_lines(client_points.data(), client_points.size());
}