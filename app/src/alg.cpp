#include "alg.h"

void convert_point_from_client_into_local(const WinApiRender &Render, const vec2 &local_point, POINT &client_point)
{
    client_point = { (LONG)roundf(local_point.x), (LONG)roundf(local_point.y) };
    Render.convert_from_client_into_local(&client_point);
}

void convert_point_arr_from_client_into_local(const WinApiRender &Render, const std::vector<vec2> &local_point_arr, std::vector<POINT> &client_point_arr)
{
    client_point_arr.resize(local_point_arr.size());

    for (size_t i = 0; i < client_point_arr.size(); ++i)
        convert_point_from_client_into_local(Render, local_point_arr[i], client_point_arr[i]);
}

void rotate(float &x, float &y, float phi)
{
    phi *= 0.017453; // пи : 180
    const float __x = x;
    const float __y = y;
    const float __c = std::cos(phi);
    const float __s = std::sin(phi);
    x = __c * __x - __s * __y;
    y = __c * __y + __s * __x;
}

float transform(int &tx, int &ty, float x, float y, float z, float phi_x, float phi_y, float phi_z, int width, int height, int zoom)
{
    const float xc = width / 2;
    const float yc = height / 2;

    rotate(y, z, phi_x);
    rotate(x, z, phi_y);
    rotate(x, y, phi_z);

    tx = (int)roundf(x * zoom + xc);
    ty = (int)roundf(y * zoom + yc);

    return z;
}

void calculateSurface(cpvec2 x_range, cpvec2 z_range, float x_step, float z_step, Formula formula, int width, int height, float scale, std::vector<std::vector<vec3>> &height_map)
{
    for (float z = z_range->y; z >= z_range->x; z -= z_step)
    {
        std::vector<vec3> line;

        for (float x = x_range->x; x <= x_range->y; x += x_step)
        {
            float y;

            switch (formula)
            {
                case F1:
                {
                    y = 0;
                    break;
                }

                case F2:
                {
                    y = x * x + z * z;
                    break;
                }

                case F3:
                {
                    y = sin(x) * sin(z);
                    break;
                }

                case F4:
                {
                    y = cos(x) * cos(z);
                    break;
                }

                case F5:
                {
                    y = acos(sin(x)) * asin(cos(z));
                    break;
                }

                case F6:
                {
                    y = (tan(sin(x + PI / 2.f)) + expf(cos(2.f * (x + PI / 2.f)))) * (cos(z) * sin(2.f * z) + sin(z));
                    break;
                }

                default:
                    y = 0.f;
                    break;
            }

            int xt, yt;
            float zt = transform(xt, yt, x, y, z, vals::x_angle, vals::y_angle, 0.f, width, height, 20 * scale);
            line.push_back(vec3({float(xt), float(yt), float(zt)}));
        }
        height_map.push_back(line);
    }

    if (height_map.front().front().z < height_map.back().front().z)
        std::reverse(height_map.begin(), height_map.end());
}

void horizon(const WinApiRender &Render, std::vector<int> &top, std::vector<int> &down, int x1, int y1, int x2, int y2)
{
    const int width = Render.get_width();

    if (x2 < x1)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    if (x2 == x1 && x2 > 0 && x2 < width)
    {
        top[x2] = std::max(top[x2], y2);
        down[x2] = std::min(down[x2], y2);

        if (0 <= x2 && x2 <= width)
            Render.draw_line(x1, y1, x2, y2);
    }
    else
    {
        const auto xp = x1;
        const auto yp = y1;
        const auto m = static_cast<double>(y2 - y1) / (x2 - x1);

        for (int x = x1; x <= x2; ++x)
        {
            if (x >= 0 && x < width)
            {
                const auto y = (int)roundf(m * (x - x1) + y1);
                top[x] = std::max(top[x], y);
                down[x] = std::min(down[x], y);

                if (0 <= x && x <= width)
                    Render.draw_line(xp, yp, x, y);
            }
        }
    }
}

void processEdge(const WinApiRender &Render, int &x, int &y, int &xEdge, int &yEdge, std::vector<int> &top, std::vector<int> &down)
{
    if (~xEdge)
        horizon(Render, top, down, xEdge, yEdge, x , y);

    xEdge = x;
    yEdge = y;
}

void intersect(int &xi, int &yi, int x1, int y1, int x2, int y2, const std::vector<int> &horizon)
{
    const int h1 = horizon[x1];
    const int h2 = horizon[x2];

    const int delta_x = x2 - x1;
    const int delta_y = y2 - y1;
    const int delta_h = h2 - h1;

    if (!delta_x) {
        xi = x2;
        yi = h2;
        return;
    }

    if (y1 == h1 && y2 == h2) {
        xi = x1;
        yi = y1;
        return;
    }

    const auto m = static_cast<float>(delta_y) / delta_x;

    xi = x1 - roundf(static_cast<float>(delta_x * (y1 - h1)) / (delta_y - delta_h));
    yi = roundf((xi - x1) * m + y1);
}

int visible(int x, int y, const std::vector<int> &top, const std::vector<int> &down)
{
    if (y >= top[x])
        return 1;
    if (y <= down[x])
        return -1;
    return 0;
}

void drawSurface(const WinApiRender &Render, cpvec2 x_range, cpvec2 z_range, float x_step, float z_step, Formula formula, COLORREF color)
{
    int width = Render.get_width();
    int height = Render.get_height();
    WinApiPen Pen(Render.get_hdc());
    std::vector<std::vector<vec3>> surface;

    Pen.select(PS_SOLID, 1, color);
    calculateSurface(x_range, z_range, x_step, z_step, formula, width, height, Render.get_scale(), surface);

    std::vector<int> top(width, 0);
    std::vector<int> down(width, height);

    int xl = -1;
    int xr = -1;
    int yl = -1;
    int yr = -1;

    for (size_t i = 0; i < surface.size(); ++i)
    {
        int xp = surface[i][0].x;
        int yp = surface[i][0].y;
        processEdge(Render, xp, yp, xl, yl, top, down);
        auto pflag = visible(xp, yp, top, down);

        for (size_t j = 0; j < surface[i].size(); ++j)
        {
            int xc = surface[i][j].x;
            int yc = surface[i][j].y;
            int xi, yi;
            auto tflag = visible(xc, yc, top, down);

            if (tflag == pflag)
            {
                if (pflag)
                    horizon(Render, top, down, xp, yp, xc, yc);
            }
            else if (!tflag)
            {
                intersect(xi, yi, xp, yp, xc, yc, pflag == 1 ? top : down);
            }
            else if (tflag == 1)
            {
                intersect(xi, yi, xp, yp, xc, yc, top);
                horizon(Render, top, down, xp, yp, xi, yi);

                if (pflag)
                {
                    intersect(xi, yi, xp, yp, xc, yc, down);
                    horizon(Render, top, down, xp, yp, xi, yi);
                }
            }
            else
            {
                intersect(xi, yi, xp, yp, xc, yc, down);
                horizon(Render, top, down, xp, yp, xi, yi);

                if (pflag)
                {
                    intersect(xi, yi, xp, yp, xc, yc, top);
                    horizon(Render, top, down, xp, yp, xi, yi);
                }
            }

            pflag = tflag;
            xp = xc;
            yp = yc;
        }

        processEdge(Render, xp, yp, xr, yr, top, down);
    }
}