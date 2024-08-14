#ifndef WINAPI_CONSOLE_H
#define WINAPI_CONSOLE_H

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <io.h>
#include <iostream>
#include <stdio.h>

#define MIN_BUFFER_SIZE 128

class WinApiConsole
{
private:
    bool redirect_io();

    void adjust_buffer();

public:
    WinApiConsole() {};
    ~WinApiConsole() {};

    bool create();

    void set_curet_pos(SHORT col, SHORT row);

    bool destroy();
};

#endif // WINAPI_CONSOLE_H