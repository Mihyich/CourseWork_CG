#ifndef WINAPI_CHOOSE_FILE_DIALOG_H
#define WINAPI_CHOOSE_FILE_DIALOG_H

#include <windows.h>

bool ChooseFileDialog(HWND hWnd, WCHAR szFile[MAX_PATH], const WCHAR *Filter, const WCHAR *InitialDir);

#endif // WINAPI_CHOOSE_FILE_DIALOG_H