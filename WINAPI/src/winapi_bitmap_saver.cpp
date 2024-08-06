#include "winapi_bitmap_saver.h"

bool gen_bitmap_header(std::ofstream &file, BITMAP &bmp, bool inverseY)
{
    if (!file.is_open())
        return false;

    bool rs = true;

    BITMAPINFOHEADER bmih = {};
    BITMAPFILEHEADER bmfh = {};

    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = bmp.bmWidth;
    bmih.biHeight = inverseY ? -bmp.bmHeight : bmp.bmHeight;
    bmih.biPlanes = 1;
    bmih.biBitCount = bmp.bmBitsPixel;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 0; // Размер изображения может быть 0 для несжатых BMP

    bmfh.bfType = 0x4D42; // Сигнатура "BM"
    bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    file.write(reinterpret_cast<const char*>(&bmfh), sizeof(BITMAPFILEHEADER));
    file.write(reinterpret_cast<const char*>(&bmih), sizeof(BITMAPINFOHEADER)); 

    return rs;
}

BYTE* create_bitmap_bit_array(const HBITMAP hBitmap)
{
    if (!hBitmap)
        return nullptr;
    
    bool rs = true;

    BYTE *buffer = nullptr;
    BITMAP bmp = {};
    int cb = 0;

    if (!GetObject(hBitmap, sizeof(BITMAP), &bmp))
        rs = false;

    if (rs && (cb = bmp.bmWidthBytes * bmp.bmHeight) <= 0)
        rs = false;

    if (rs && !(buffer = new BYTE[cb]))
        rs = false;

    if (rs && !GetBitmapBits(hBitmap, bmp.bmWidthBytes * bmp.bmHeight, buffer))
        rs = false;

    if (!rs && buffer)
    {
        delete[] buffer;
        buffer = nullptr;
    }

    return buffer;
}

bool save_bitmap(const wchar_t *file_name, const HBITMAP hBitmap, bool inverseY)
{
    if (!file_name || !hBitmap)
        return false;

    bool rs = true;
    std::wstring name(file_name);
    std::ofstream file;
    BITMAP bmp = {};
    BYTE* buffer = nullptr;

    name += L".bmp";

    if (rs && !GetObject(hBitmap, sizeof(BITMAP), &bmp))
        rs = false;

    // открыть файл
    if (rs)
    {
        file.open(name.c_str(), std::ios::binary);

        if (!file)
            rs = false;
    }

    // создать заголовок файла bmp
    if (rs)
        rs = gen_bitmap_header(file, bmp, inverseY);

    // создать 
    if (rs && !(buffer = create_bitmap_bit_array(hBitmap)))
        rs = false;

    // Записать данные пикселей в файл
    if (rs)
        file.write(reinterpret_cast<const char*>(buffer), bmp.bmWidthBytes * bmp.bmHeight);

    // очистить память
    if (buffer)
    {
        delete[] buffer;
        buffer = nullptr;
    }

    return rs;
}

bool save_bitmap(const wchar_t *file_name, const HDC hDc, bool inverseY)
{
    if (!file_name || !hDc)
        return false;

    bool rs = true;
    RECT rect = {0, 0, 0, 0};
    int width = 0;
    int height = 0;
    HDC hMemDC = nullptr;
    HBITMAP hBitmap = nullptr;
    HBITMAP hOldBitmap = nullptr;
    
    // Получаем размеры изображения из HDC
    if (!GetClipBox(hDc, &rect))
    {
        rs = false;
    }
    else
    {
        width = get_rect_width(rect);
        height = get_rect_height(rect);
    }

    // Создаем совместимый DC
    if (rs && !(hMemDC = CreateCompatibleDC(hDc)))
        rs = false;

    // Создаем совместимый битмап 
    if (rs && !(hBitmap = CreateCompatibleBitmap(hDc, width, height)))
        rs = false;

    // Копируем содержимое HDC в битмап
    if (rs)
    {
        hOldBitmap = reinterpret_cast<HBITMAP>(SelectObject(hMemDC, hBitmap));
        rs = BitBlt(hMemDC, 0, 0, width, height, hDc, rect.left, rect.top, SRCCOPY);
    }

    // Сохраняем битмап в файл BMP по hbitmap
    if (rs)
        rs = save_bitmap(file_name, hBitmap, inverseY);

    // Восстанавливаем и освобождаем ресурсы
    if (hMemDC)
    {
        if (hOldBitmap) SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }


    return rs;
}