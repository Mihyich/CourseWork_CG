#ifndef MODEL_LOADER_DIALOG_PROC_H
#define MODEL_LOADER_DIALOG_PROC_H

#include <windows.h>

#include "resource.h"

#include "winapi_mat_ext.h"
#include "winapi_choose_file_dialog.h"
#include "winapi_font_common.h"
#include "winapi_font.h"

#include "user_msgs.h"
#include "app_args.h"

LRESULT CALLBACK ModelLoaderDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif // MODEL_LOADER_DIALOG_PROC_H