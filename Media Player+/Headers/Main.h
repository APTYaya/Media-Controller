#pragma once

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>



#define BTN_PREV     1
#define BTN_PLAYPAUSE 2
#define BTN_NEXT     3

extern void SendMediaKey(WORD keyCode);

extern void VolumeControl(int volume);

extern LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);