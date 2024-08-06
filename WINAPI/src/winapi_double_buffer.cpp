#include "winapi_double_buffer.h"

void WinApiDoubleBuffer::init(HWND hWnd)
{
    this->hWnd = hWnd;
	this->hMemFrameDC = nullptr;
	this->hMemFrameBitMap = nullptr;
}

void WinApiDoubleBuffer::resize_buffer(HDC hDc)
{
    if (!hDc)
        return;

    destroy_buffer();

    RECT rect;

    GetClientRect(this->hWnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

	hMemFrameDC = CreateCompatibleDC(hDc);
	hMemFrameBitMap = CreateCompatibleBitmap(hDc, width, height);
}

void WinApiDoubleBuffer::bind_buffer()
{
    if (!hMemFrameDC || !hMemFrameBitMap)
        return;

    SelectObject(hMemFrameDC, hMemFrameBitMap);
	SetGraphicsMode(hMemFrameDC, GM_ADVANCED);
}

void WinApiDoubleBuffer::swap_buffer(HDC hDc) const
{
    if (!hDc || !hMemFrameDC)
    {
        return;
    }
    
	BitBlt(hDc, 0, 0, width, height, hMemFrameDC, 0, 0, SRCCOPY);
}

HDC WinApiDoubleBuffer::get_hMemFrameDC(void) const
{
    return this->hMemFrameDC;
}

HBITMAP WinApiDoubleBuffer::get_hMemFrameBitMap(void) const
{
    return this->hMemFrameBitMap;
}

void WinApiDoubleBuffer::destroy_buffer(void)
{
    if (hMemFrameDC)
    {
        DeleteObject(hMemFrameDC);
        hMemFrameDC = nullptr;
    }

	if (hMemFrameBitMap) 
    {
        DeleteObject(hMemFrameBitMap);
        hMemFrameBitMap = nullptr;
    }
}

WinApiDoubleBuffer::~WinApiDoubleBuffer()
{
    destroy_buffer();
}