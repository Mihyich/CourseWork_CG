#include "winapi_choose_file_dialog.h"

bool ChooseFileDialog(HWND hWnd, WCHAR szFile[MAX_PATH], const WCHAR *Filter, const WCHAR *InitialDir)
{
    OPENFILENAME ofn;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = sizeof(WCHAR) * MAX_PATH;
    ofn.lpstrFilter = Filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = InitialDir;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    memset(szFile, 0, MAX_PATH * sizeof(WCHAR));

    return GetOpenFileName(&ofn);
}