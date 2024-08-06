#include "winapi_render.h"

void WinApiRender::init(HWND hWnd)
{
    this->hWnd = hWnd;
    vec2_set(&origin, 0, 0 );
    scale_rol = 0;
    scale = powf(2.f, (float)scale_rol / SCALE_ROL_BROAD);
    dynamic_expanded_grid = true;
    Dbuffer.init(this->hWnd);
    hDc = nullptr;
    hmemDc = nullptr;
}

void WinApiRender::start(void)
{
    hDc = BeginPaint(hWnd, &ps);
    this->hmemDc = Dbuffer.get_hMemFrameDC();
    Dbuffer.bind_buffer();
}

void WinApiRender::swap_buffer(void) const
{
    Dbuffer.swap_buffer(hDc);
}

void WinApiRender::end(void)
{
    EndPaint(hWnd, &ps);
    hDc = nullptr;
    hmemDc = nullptr;
}

void WinApiRender::draw_background(COLORREF color) const
{
    // Интструменты рисования
    WinApiPen Pen(this->hmemDc);
	WinApiBrush Brush(this->hmemDc);
    // Подготовить инструменты
    Pen.select(PS_SOLID, 1, color);
    Brush.select_solid(color);
	// рисование
	Rectangle(this->hmemDc, 0, 0, this->size.x, this->size.y);
}

void WinApiRender::draw_pixel(const POINT &pos, int size) const
{
    if (!hmemDc || size < 1 || !WA_IS_CLAMP(pos.x, 0, this->size.x) || !WA_IS_CLAMP(pos.y, 0, this->size.y))
        return;

    // размер 1
    if (size == 1)
    {
        SetPixel(this->hmemDc, pos.x, pos.y, GetPenColorFromDC(this->hmemDc));
    }
    else
    {
        int hs = size / 2;

        // нечетный размер
        if (size % 2)
        {
            Rectangle(
                this->hmemDc,
                pos.x - hs, pos.y - hs,
                pos.x + hs, pos.y + hs
            );

        }
        // четный размер
        else
        {
            Rectangle(
                this->hmemDc,
                pos.x - hs, pos.y - hs,
                pos.x + hs - 1, pos.y + hs - 1
            );
        }
    }
}

void WinApiRender::draw_pixels(const POINT *pos, size_t count, int size) const
{
    if (!pos)
        return;

    const POINT *end = pos + count;

    for (const POINT *cur = pos; cur < end; ++cur)
        draw_pixel(*cur, size);
}

void WinApiRender::draw_pixels_simmetric(const POINT &center, const POINT &diff, int size) const
{
    const POINT pixels[4] = {
        {center.x + diff.x, center.y + diff.y},
        {center.x - diff.x, center.y - diff.y},
        {center.x + diff.x, center.y - diff.y},
        {center.x - diff.x, center.y + diff.y}
    };

    draw_pixels(pixels, 4, size);
}

void WinApiRender::draw_point(float x, float y)
{
    if (!hmemDc)
        return;

    Ellipse(
        this->hmemDc,
        x - POINT_SIZE / 2.f, y + POINT_SIZE / 2.f,
        x + POINT_SIZE / 2.f, y - POINT_SIZE / 2.f
    );
}

void WinApiRender::draw_point_arr(cpvec2 arr, size_t count, COLORREF COL)
{
    // кисти
    HBRUSH old_brush;
	HBRUSH point_brush;
    // перевод
    vec2 tmp;
    // создание кистей
    point_brush = (HBRUSH)CreateSolidBrush(COL);
	old_brush = (HBRUSH)SelectObject(this->hmemDc, point_brush);
    // рисование
    for (size_t i = 0; i < count; ++i)
    {
        tmp = *arr;
        vec2_add(&tmp, &this->origin);
        mat3_transform_vec2(&this->proj, &tmp);
        draw_point(tmp.x, tmp.y);
        ++arr;
    }
    // очистка
	DeleteObject((HBRUSH)SelectObject(this->hmemDc, old_brush));
}

void WinApiRender::draw_point_arr(cpvec2 arr, const int *valid, size_t count, COLORREF COL)
{
    // кисти
    HBRUSH old_brush;
	HBRUSH point_brush;
    // перевод
    vec2 tmp;
    // создание кистей
    point_brush = (HBRUSH)CreateSolidBrush(COL);
	old_brush = (HBRUSH)SelectObject(this->hmemDc, point_brush);
    // рисование
    for (size_t i = 0; i < count; ++i)
    {
        if (*valid)
        {
            tmp = *arr;
            vec2_add(&tmp, &this->origin);
            mat3_transform_vec2(&this->proj, &tmp);
            draw_point(tmp.x, tmp.y);
        }

        ++arr;
        ++valid;
    }
    // очистка
	DeleteObject((HBRUSH)SelectObject(this->hmemDc, old_brush));
}

void WinApiRender::draw_line(int x1, int y1, int x2, int y2) const
{
    if (!hmemDc)
        return;

    MoveToEx(this->hmemDc, x1, y1, NULL);
	LineTo(this->hmemDc, x2, y2);
}

void WinApiRender::draw_line(float x1, float y1, float x2, float y2) const
{
    draw_line(
        (int)roundf(x1), (int)roundf(y1),
        (int)roundf(x2), (int)roundf(y2));
}

void WinApiRender::draw_line(const POINT &p1, const POINT &p2) const
{
    draw_line(
        (int)p1.x, (int)p1.y,
        (int)p2.x, (int)p2.y);
}

void WinApiRender::draw_lines(const POINT *points, size_t count) const
{
    if (!points || !count)
        return;

    for (size_t i = 1; i < count; i += 2)
        draw_line(*(points + (i - 1)), *(points + i));
}

void WinApiRender::draw_polyline(const POINT *points, size_t count) const
{
    if (!points || count < 2 || !this->hmemDc)
        return;

    Polyline(this->hmemDc, points, count);
}

void WinApiRender::draw_line_strip(const POINT *points, size_t count) const
{
    if (!points || count < 2)
        return;

    draw_polyline(points, count);
    draw_line(*(points + count - 1), *points);
}

void WinApiRender::draw_grid(float step)
{
	// ручка
    WinApiPen Pen(this->hmemDc);
    // вспомогательные переменные
    vec2 start_pos;
	vec2 client_pos;
    // изменить шаг
    if (this->dynamic_expanded_grid) step = dyn_ex_step(step);
    // Выбрать цвет
    Pen.select(PS_SOLID, 1, RGB(0, 0, 0));
    // вычислить периодический центр рисования сетки
    vec2_division(&origin, step, &start_pos);
    vec2_set(&start_pos, modff(start_pos.x, &start_pos.x), modff(start_pos.y, &start_pos.y));
    vec2_scale(&start_pos, step);
    mat3_transform_vec2(&this->proj, &start_pos);
    step *= scale;
    // сетка вправо
    client_pos = start_pos;
    while (client_pos.x < size.x)
    {
        draw_line(client_pos.x, 0.f, client_pos.x, size.y);
        client_pos.x += step;
    }
    // стека вниз
    while (client_pos.y < size.y)
    {
        draw_line(0.f, client_pos.y, size.x, client_pos.y);
        client_pos.y += step;
    }
    // сетка влево
    client_pos = start_pos;
    client_pos.x -= step;
    client_pos.y -= step;
    while (client_pos.x > 0)
    {
        draw_line(client_pos.x, 0.f, client_pos.x, size.y);
        client_pos.x -= step;
    }
    // стека вверх
    while (client_pos.y > 0)
    {
        draw_line(0.f, client_pos.y, size.x, client_pos.y);
        client_pos.y -= step;
    }
    // Выбрать цвет
    Pen.select(PS_SOLID, 4, RGB(50, 50, 50));
    // рисование начала координат
    client_pos = this->origin;
    mat3_transform_vec2(&this->proj, &client_pos);
    // ось абсцисс
    if (client_pos.y >= 0 && client_pos.y <= size.y)
        draw_line(0.f, client_pos.y, size.x, client_pos.y);
    // ось ординат
    if (client_pos.x >= 0 && client_pos.x <= size.x)
        draw_line(client_pos.x, 0.f, client_pos.x, size.y);
}

void WinApiRender::draw_rect(int l, int t, int r, int b) const
{
    if (!hmemDc)
        return;

    Rectangle(this->hmemDc, l, t, r, b);
}

void WinApiRender::draw_rect(const POINT &lt, const  POINT &rb) const
{
    draw_rect(lt.x, lt.y, rb.x, rb.y);
}

void WinApiRender::draw_rect(const RECT *rect) const
{
    draw_rect(rect->left, rect->top, rect->right, rect->bottom);
}

void WinApiRender::draw_ellipse(const INT l, const INT t, const INT r, const INT b) const
{
    if (!hmemDc)
        return;

    Ellipse(this->hmemDc, l, t, r, b);
}

void WinApiRender::draw_ellipse(const POINT *lt, const POINT *rb) const
{
    if (!lt || !rb)
        return;

    draw_ellipse(lt->x, lt->y, rb->x, rb->y);
}

void WinApiRender::draw_ellipse(const RECT *rect) const
{
    if (!rect)
        return;

    draw_ellipse(rect->left, rect->top, rect->right, rect->bottom); 
}

void WinApiRender::draw_ellipse(const POINT *position, const float radius_x, const float radius_y) const
{
    if (!position) 
        return;

    RECT rect = {
        position->x - (LONG)radius_x, position->y - (LONG)radius_y,
        position->x + (LONG)radius_x, position->y + (LONG)radius_y
    };

    draw_ellipse(&rect);
}

void WinApiRender::draw_circle(const POINT *position, const float radius) const
{
    if (!position) 
        return;

    RECT rect = {
        position->x - (LONG)radius, position->y - (LONG)radius,
        position->x + (LONG)radius, position->y + (LONG)radius
    };

    draw_ellipse(&rect);
}

void WinApiRender::draw_arc(const INT x1, const INT y1, const INT x2, const INT y2, const INT x3, const INT y3, const INT x4, const INT y4) const
{
    if (!hmemDc)
        return;

    Arc(this->hmemDc, x1, y1, x2, y2, x3, y3, x4, y4);
}

void WinApiRender::draw_arc(const RECT *rect, const POINT *s, const POINT *e) const
{
    if (!rect || !s || !e)
        return;

    draw_arc(rect->left, rect->top, rect->right, rect->bottom, s->x, s->y, e->x, e->y);
}

void WinApiRender::draw_arc(const RECT *rect, float ang1, float ang2) const
{
    if (!rect)
        return;

    POINT center;
    LONG xradius;
    LONG yradius;
    LONG max_radius;
    POINT s, e;
    float radian1, radian2;

    get_rect_center(*rect, center);
    xradius = get_rect_width(*rect);
    yradius = get_rect_height(*rect);
    max_radius = std::max(xradius, yradius);
    radian1 = degrees_to_radians(ang1);
    radian2 = degrees_to_radians(ang2);

    s.x = center.x + max_radius * cosf(radian1);
    s.y = center.y + max_radius * sinf(radian1);

    e.x = center.x + max_radius * cosf(radian2);
    e.y = center.y + max_radius * sinf(radian2);

    draw_arc(rect, &s, &e);
}

void WinApiRender::draw_ring(const INT l, const INT t, const INT r, const INT b) const
{
    draw_arc(l, t, r, b, 0, 0, 0, 0);
}

void WinApiRender::draw_ring(const RECT *rect) const
{
    if (!rect)
        return;

    draw_ring(rect->left, rect->top, rect->right, rect->bottom);
}

void WinApiRender::draw_ring(const POINT *lt, const POINT *rb) const
{
    if (!lt || !rb)
        return;

    draw_arc(lt->x, lt->y, rb->x, rb->y, 0, 0, 0, 0);
}

void WinApiRender::draw_ring(const POINT *position, const float radius) const
{
    if (!position)
        return;

    RECT rect = {
        position->x - (LONG)radius, position->y - (LONG)radius,
        position->x + (LONG)radius, position->y + (LONG)radius
    };

    draw_ring(&rect);
}

void WinApiRender::draw_ring(const POINT *position, const float radius_x, const float radius_y) const
{
    if (!position)
        return;

    RECT rect = {
        position->x - (LONG)radius_x, position->y - (LONG)radius_y,
        position->x + (LONG)radius_x, position->y + (LONG)radius_y
    };

    draw_ring(&rect);
}

void WinApiRender::update_proj(void)
{
    this->proj.x_basis.x = scale;
    this->proj.x_basis.y = 0.f;
    this->proj.x_basis.z = 0.f;

    this->proj.y_basis.x = 0.f;
    this->proj.y_basis.y = -scale;
    this->proj.y_basis.z = 0.f;

    this->proj.z_basis.x = size.x / 2.f;
    this->proj.z_basis.y = size.y / 2.f;
    this->proj.z_basis.z = 1.f;

    this->proj_inv = proj;
    mat3_inverse(&this->proj_inv);
}

void WinApiRender::update_buffer_size(void)
{
    const HDC hDc = GetDC(hWnd);
    Dbuffer.resize_buffer(hDc);
    ReleaseDC(hWnd, hDc);
}

void WinApiRender::update_size(void)
{
    get_wnd_size(&this->size);
    update_proj();
    update_buffer_size();
}

void WinApiRender::update_origin(pvec2 dt)
{
    vec2_scaled_add(&this->origin, dt, 1.f / this->scale);
}

void WinApiRender::update_scale(int dt)
{
    this->scale_rol += dt;

    if (this->scale_rol < MIN_ROL_BROAD)
        this->scale_rol = MIN_ROL_BROAD;

    if (this->scale_rol > MAX_ROL_BROAD)
        this->scale_rol = MAX_ROL_BROAD;

    this->scale = powf(2.f, (float)(scale_rol) / SCALE_ROL_BROAD);

    update_proj();
}

void WinApiRender::update_scale_via_point(int dt, cpvec2 loc_mouse_pos)
{
    POINT point;
    vec2 new_mouse_pos;
    // обновить масштаб
    update_scale(dt);
    // получить новые данные мыши
    GetCursorPos(&point);
    ScreenToClient(hWnd, &point);
    // перевод в локальную систему координат
    new_mouse_pos.x = (float)point.x;
    new_mouse_pos.y = (float)point.y;
    convert_from_local_into_client(&new_mouse_pos);
    // сдвинуть картинку под мышь
    vec2_add(&origin, &new_mouse_pos);
    vec2_sub(&origin, loc_mouse_pos);
}

void WinApiRender::convert_from_client_into_local(pvec2 coord) const
{
    mat3_transform_vec2(&this->proj, coord);
    coord->x += this->origin.x * this->scale;
    coord->y -= this->origin.y * this->scale;
}

void WinApiRender::convert_from_client_into_local(float *x, float *y) const
{
    vec2 temp = { *x, *y };
    convert_from_client_into_local(&temp);
    *x = temp.x;
    *y = temp.y;
}

void WinApiRender::convert_from_client_into_local(POINT *coord) const
{
    vec2 temp = { (float)coord->x, (float)coord->y };
    convert_from_client_into_local(&temp);
    coord->x = temp.x;
    coord->y = temp.y;
}

void WinApiRender::convert_from_local_into_client(pvec2 coord) const
{
    mat3_transform_vec2(&this->proj_inv, coord);
    vec2_sub(coord, &this->origin);
}

void WinApiRender::convert_from_local_into_client(float *x, float *y) const
{
    vec2 temp = { *x, *y };
    convert_from_local_into_client(&temp);
    *x = temp.x;
    *y = temp.y;
}

void WinApiRender::convert_from_local_into_client(POINT *coord) const
{
    vec2 temp = { (float)coord->x, (float)coord->y };
    convert_from_local_into_client(&temp);
    coord->x = temp.x;
    coord->y = temp.y;
}

void WinApiRender::set_origin(float x, float y)
{
    this->origin.x = x;
    this->origin.y = y;
}

void WinApiRender::set_scale_rol(int scale_rol)
{
    this->scale_rol = scale_rol;

    if (this->scale_rol < MIN_ROL_BROAD)
        this->scale_rol = MIN_ROL_BROAD;

    if (this->scale_rol > MAX_ROL_BROAD)
        this->scale_rol = MAX_ROL_BROAD;

    this->scale = powf(2.f, (float)(scale_rol) / SCALE_ROL_BROAD);

    this->update_proj();
}

int WinApiRender::get_width(void) const
{
    return size.x;
}

int WinApiRender::get_height(void) const
{
    return size.y;
}

COLORREF WinApiRender::get_pixel_color(int x, int y) const
{
    if (!this->hmemDc)
        return RGB(0, 0, 0);

    COLORREF color = GetPixel(this->hmemDc, x, y);

    if (color == CLR_INVALID)
        color = RGB(0, 0, 0);

    return color;
}

COLORREF WinApiRender::get_pixel_color(const POINT &coord) const
{
    return get_pixel_color((int)coord.x, (int)coord.y);
}

int WinApiRender::get_pixel_size(void) const
{
    int size = (int)roundf(scale);

    if (size < 1)
    {
        size = 1;
    }

    return size;
}

float WinApiRender::get_scale(void) const
{
    return this->scale;
}

void WinApiRender::get_proj(pmat3 proj) const
{
    mat3_set_basises(
        proj,
        &(this->proj.x_basis),
        &(this->proj.y_basis),
        &(this->proj.z_basis)
    );
}

void WinApiRender::get_view(pmat3 view) const
{
    get_proj(view);
    mat3_translate(view, origin.x, origin.y);
}

HDC WinApiRender::get_hdc(void) const
{
    return this->Dbuffer.get_hMemFrameDC();
}

HBITMAP WinApiRender::get_hMemBitmap(void) const
{
    return this->Dbuffer.get_hMemFrameBitMap();
}

void WinApiRender::get_wnd_size(POINT *size) const
{
    RECT rect = { 0, 0, 0, 0};
    GetClientRect(this->hWnd, &rect);
    size->x = rect.right - rect.left;
    size->y = rect.bottom - rect.top;
}

float WinApiRender::dyn_ex_step(float step) const
{
    int k;
    float koef = 1.f;

    if (scale > 1.0f)
    {
        k = (int)floorf(log2f(scale));
        koef = k > 0 ? 1.f / powf(2.f, k) : 1.f;
    }

    if (scale < 1.f)
    {
        k = -(int)ceilf(log2f(scale));
        koef = k > 0 ? powf(2.f, k) : 1.f;
    }

    return step * koef;
}