#include "Main.h"



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
	case WM_CREATE:
		/*
		InitializeTimers();
		OutputDebugString(L"Timer Initialized\n");
        return 0;
        */
    case WM_PAINT:
        return 0;

    case WM_SIZE:
        return 0;


    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case BTN_PREV:
            SendMediaKey(VK_MEDIA_PREV_TRACK);
            break;
        case BTN_PLAYPAUSE:
            SendMediaKey(VK_MEDIA_PLAY_PAUSE);
            break;
        case BTN_NEXT:
            SendMediaKey(VK_MEDIA_NEXT_TRACK);
            break;
        case BTN_POPUP:
            if (hwndVolumeMenu == NULL) {
                VolumeMenu(hwnd);
            }
            else {
                DestroyWindow(hwndVolumeMenu);
                hwndVolumeMenu = NULL;
            }
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}




