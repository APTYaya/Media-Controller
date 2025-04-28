#include "Main.h"

HWND hwndVolumeMenu = NULL;

LRESULT CALLBACK PopupWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HWND hwndSystemVolumeSlider = NULL;
    switch (uMsg) {
    case WM_CREATE:
        return 0;

    case WM_HSCROLL
		:
			hwndSystemVolumeSlider = (HWND)lParam;
			if (hwndSystemVolumeSlider) {
				int volumePercent = SendMessage(hwndSystemVolumeSlider, TBM_GETPOS, 0, 0);
				SetSystemVolume(volumePercent);
			}
			return 0;

    case WM_KILLFOCUS:
		hwndSystemVolumeSlider = (HWND)wParam;

        if (!IsChild(hwnd, hwndSystemVolumeSlider)) {
            DestroyWindow(hwnd);
            hwndVolumeMenu = NULL;
        }
        return 0;

    case WM_DESTROY:
        hwndVolumeMenu = NULL;  
		UnregisterClassW(L"VolumeMenuWindow", GetModuleHandle(NULL));
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void VolumeMenu(HWND parentHwnd) {
    if (hwndVolumeMenu != NULL) {
        DestroyWindow(hwndVolumeMenu);
        hwndVolumeMenu = NULL;  
    }

    const wchar_t CLASS_NAME[] = L"VolumeMenuWindow";

    WNDCLASS wc = {};
    if (!GetClassInfo(GetModuleHandle(NULL), CLASS_NAME, &wc)) {
        wc.lpfnWndProc = PopupWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = CLASS_NAME;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

        if (!RegisterClass(&wc)) {
            return;
        }
    }

    POINT pt;
    GetCursorPos(&pt);

    hwndVolumeMenu = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Volume Menu",
        WS_POPUP | WS_BORDER | WS_CAPTION,
        pt.x, pt.y, 
        200, 200,    
        parentHwnd, NULL, wc.hInstance, NULL
    );

	HWND hwndSystemVolumeSlider = CreateWindowEx(
		WS_EX_CONTROLPARENT,
		TRACKBAR_CLASS,
		L"System Volume",
		WS_CHILD | WS_VISIBLE, 
		10, 10, 180, 30,
		hwndVolumeMenu, NULL, wc.hInstance, NULL
	);
	SendMessage(hwndSystemVolumeSlider, TBM_SETRANGE, TRUE, MAKELONG(0, 100));

    if (hwndVolumeMenu) {
        ShowWindow(hwndVolumeMenu, SW_SHOW);
        SetForegroundWindow(hwndVolumeMenu);  
        UpdateWindow(hwndVolumeMenu);
    }
}