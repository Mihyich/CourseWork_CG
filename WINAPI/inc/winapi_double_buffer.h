#ifndef DOUBLE_BUFFER
#define DOUBLE_BUFFER

#include <windows.h>

class WinApiDoubleBuffer
{
public:

    void init(HWND hWnd);

    void resize_buffer(HDC hDc);

    void bind_buffer();

    void swap_buffer(HDC hDc) const;

    HDC get_hMemFrameDC(void) const;

    HBITMAP get_hMemFrameBitMap(void) const;

private:

    HWND hWnd = nullptr;
	HDC hMemFrameDC = nullptr;
	HBITMAP hMemFrameBitMap = nullptr;

    int width;
    int height;

    void destroy_buffer(void);

public:
    ~WinApiDoubleBuffer();
};

#endif // DOUBLE_BUFFER