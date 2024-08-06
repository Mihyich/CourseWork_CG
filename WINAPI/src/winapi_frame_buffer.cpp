#include "winapi_frame_buffer.h"

WinApiFrameBuffer::WinApiFrameBuffer()
{
    hDc = nullptr;
    pixels = nullptr;
    data = nullptr;
    width = height = 0;
}

WinApiFrameBuffer::WinApiFrameBuffer(HDC hDc)
{
    this->hDc = hDc;
    
    if (this->hDc)
    {
        RECT rect;
        GetClipBox(this->hDc, &rect);

        width = get_rect_width(rect);
        height = get_rect_height(rect);
    }
    else
    {
        width = 0;
        height = 0;
    }

    pixels = nullptr;
    data = nullptr;
}

WinApiFrameBuffer::~WinApiFrameBuffer()
{
    free_pixels_data();
}

void WinApiFrameBuffer::free_pixels_data(void)
{
    if (pixels)
    {
        delete[] pixels;
        pixels = nullptr;
    }

    if (data)
    {
        delete[] data;
        data = nullptr;
    }

    width = height = 0;
}

bool WinApiFrameBuffer::malloc_pixels_data(int width, int height)
{
    if (width <= 0 || height <= 0)
        return false;

    bool rs = true;
    COLORREF** pointers = new COLORREF* [height];
    COLORREF* matrix = nullptr;

    if (!pointers)
    {
        rs = false;
    }
    else
    {
        matrix = new COLORREF [width * height];

        if (!matrix)
        {
            delete[] pointers;
            rs = false;
        }
        else
        {
            for (int i = 0; i < height; ++i)
            {
                pointers[i] = matrix + i * width;
            }

            free_pixels_data();

            this->pixels = pointers;
            this->data = matrix;
            this->width = width;
            this->height = height;
        }
    }

    return rs;
}

bool WinApiFrameBuffer::create_pixel_matrix_from_hdc(void)
{
    if (!hDc || width <= 0 || height <= 0)
        return false;

    bool rs = true;

    // Создание DIBSection для копирования содержимого HDC
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32 бита на пиксель (ARGB)
    bmi.bmiHeader.biCompression = BI_RGB; // без сжатия

    HBITMAP hBitmap = CreateDIBSection(hDc, &bmi, DIB_RGB_COLORS, nullptr, NULL, 0);

    // Обработка ошибки
    if (hBitmap == NULL)
    {
        return false;
    }

    // Копирование содержимого HDC в DIBSection
    HDC memDC = CreateCompatibleDC(hDc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(memDC, 0, 0, width, height, hDc, 0, 0, SRCCOPY);

    // Получение массива пикселей из DIBSection
    rs = create_pixel_matrix_from_hbitmap(hBitmap);

    // Освобождение ресурсов
    SelectObject(memDC, hOldBitmap);
    DeleteDC(memDC);
    DeleteObject(hBitmap);

    return rs;
}

bool WinApiFrameBuffer::create_pixel_matrix_from_hbitmap(const HBITMAP hBitmap)
{
    if (!hBitmap)
        return false;

    bool rs = true;
    BITMAP bmp = {}; // инфа о bitmap
    BYTE* buffer = nullptr;
    LONG cb = 0;

    // Получить информацию о битмапе
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    // рассчитать необходимое кол-во байтов
    if (!(cb = bmp.bmWidthBytes * bmp.bmHeight))
    {
        rs = false;
    }

    // выделить память под буфер
    if (rs)
    {
        buffer = new BYTE [cb];

        if (!buffer)
        {
            rs = false;
        }
    }

    // Cкопировать данные пикселей в буфер
    if (rs && !GetBitmapBits(hBitmap, bmp.bmWidthBytes * bmp.bmHeight, buffer))
    {
        rs = false;
    }

    // Выделить данные под пиксели
    if (rs)
    {
        rs = malloc_pixels_data(bmp.bmWidth, bmp.bmHeight);
    }

    // скопировать пиксели в локальный массив
    if (rs)
    {
        for (int y = 0; y < bmp.bmHeight; ++y)
        {
            BYTE* row = buffer + (bmp.bmHeight - y - 1) * bmp.bmWidthBytes;

            for (int x = 0; x < bmp.bmWidth; ++x)
            {
                BYTE* pixel = row + x * 4; // Каждый пиксель занимает 4 байта (ARGB)
                pixels[bmp.bmHeight - y - 1][x] = RGB(pixel[2], pixel[1], pixel[0]); // Преобразование формата пикселя
            }
        }
    }

    if (buffer)
    {
        delete[] buffer;
        buffer = nullptr;
    }

    return rs;
}

void WinApiFrameBuffer::copy_mask(WinApiFrameBuffer &fb, COLORREF color)
{
    if (!pixels || !data || width <= 0 || height <= 0)
        return;

    const int cpwidth = std::min(width, (int)fb.get_col_count());
    const int cpheight = std::min(height, (int)fb.get_row_count());

    for (int y = 0; y < cpheight; ++y)    
    {
        for (int x = 0; x < cpwidth; ++x)
        {
            if (fb[y][x] == color)
                pixels[y][x] = color;
        }
    }
}

void WinApiFrameBuffer::copy_into_hdc(const HDC hDc) const
{
    if (!hDc || !pixels || !data || width <= 0 || height <= 0)
        return;

    RECT rect;
    GetClipBox(hDc, &rect);

    const int src_width = get_rect_width(rect);
    const int src_height = get_rect_height(rect);
    const size_t size = width * height;

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // Отрицательное значение, чтобы изображение отображалось с верха вниз
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32 бита на пиксель (ARGB)
    bmi.bmiHeader.biCompression = BI_RGB;

    // временная копия пикселей
    std::vector<COLORREF> rev_pixels(data, data + size);

    // развернуть байты цветов
    reverse_color_str(&rev_pixels[0], &rev_pixels[size - 1]);

    // копирование пикселей
    SetDIBitsToDevice(
        hDc,
        0, 0, src_width, src_height,
        0, 0,
        0, height,
        rev_pixels.data(), &bmi, DIB_RGB_COLORS
    );
}

bool WinApiFrameBuffer::save(const wchar_t *file_name) const
{
    if (!file_name || !pixels || !data || width <= 0 || height <= 0)
        return false;

    std::wstring name(file_name);
    name += L".bmp";

    std::ofstream file(name.c_str(), std::ios::binary);

    if (!file)
        return false;

    // Заголовок BMP файла
    BITMAPFILEHEADER bmfh = {};
    BITMAPINFOHEADER bmih = {};

    int width_bytes = (width * 32 + 31) / 32 * 4; // Выравнивание ширины строки

    bmfh.bfType = 0x4D42; // Сигнатура "BM"
    bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width_bytes * height;
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = width;
    bmih.biHeight = -height; // перевернуть Y
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 0; // Размер изображения может быть 0 для несжатых BMP

    // Запись заголовков в файл
    file.write(reinterpret_cast<const char*>(&bmfh), sizeof(BITMAPFILEHEADER));
    file.write(reinterpret_cast<const char*>(&bmih), sizeof(BITMAPINFOHEADER));

    // Запись данных пикселей в файл
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            COLORREF pixel = color_reverse(pixels[y][x]); // Долго объеснять. Если коротко картинка хранится кверх-ногами, но когда копируется в массив принимаем, что там не кверх-ногами (чтобы удобно полбзоваться перегрузкой []), а уже когда сохраняем, то те крверх-ноги поломали послед. байт окончательно...
            file.write(reinterpret_cast<const char*>(&pixel), sizeof(COLORREF));
        }

        // Дополнить строку до выравнивания
        int padding = width_bytes - width * sizeof(COLORREF);

        if (padding > 0)
        {
            COLORREF padding_color = RGB(0, 0, 0); // Черный цвет
            file.write(reinterpret_cast<const char*>(&padding_color), padding);
        }
    }

    return true;
}

void WinApiFrameBuffer::set_hdc(HDC hDc)
{
    this->hDc = hDc;
}

int WinApiFrameBuffer::get_col_count(void) const
{
    return width;
}

int WinApiFrameBuffer::get_row_count(void) const
{
    return height;
}

COLORREF* WinApiFrameBuffer::operator[](int index)
{
    if (!pixels || !data || index < 0 || index >= height)
        return nullptr;

    return *(pixels + index);
}