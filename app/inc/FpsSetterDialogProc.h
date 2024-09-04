#ifndef FPS_SETTER_DIALOG_PROC_H
#define FPS_SETTER_DIALOG_PROC_H

#include <windows.h>

#include "resource.h"

#include "winapi_mat_ext.h"
#include "winapi_choose_file_dialog.h"
#include "winapi_font_common.h"
#include "winapi_font.h"

#include "user_msgs.h"
#include "formater.h"
#include "app_args.h"

LRESULT CALLBACK FpsSetterDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif // FPS_SETTER_DIALOG_PROC_H