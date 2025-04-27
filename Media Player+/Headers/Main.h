#pragma once

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <Audioclient.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <combaseapi.h>
#include <endpointvolume.h>
#include <objbase.h>
#include <commctrl.h>



// Button IDs
#define BTN_PREV     1
#define BTN_PLAYPAUSE 2
#define BTN_NEXT     3
#define BTN_POPUP    4 

// Media Key Functions
extern void SendMediaKey(WORD keyCode);

// Volume Control Functions
extern int GetSystemVolume();
extern int GetAppVolume();
extern void VolumeControl(int volume);

// Menu/Button Functions
// extern void ButtonDrawing();
extern void VolumeMenu(HWND parentHwnd);
extern HWND hwndVolumeMenu;

// Window Procedures 
extern LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK PopupWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);