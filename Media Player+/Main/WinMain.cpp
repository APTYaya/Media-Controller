#include "Main.h"

HWND MediaController = NULL;


// Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&icex);

    const wchar_t CLASS_NAME[] = L"MediaControllerWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Main Window
    MediaController = CreateWindowEx(
        WS_EX_TOPMOST,
        CLASS_NAME,
        L"Media Controller",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        300, 150,
        NULL, NULL, hInstance, NULL
    );

	// Create buttons
    if (!MediaController)
        return 0;
    CreateWindow(L"BUTTON", L"Previous", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 30, 80, 30, MediaController, (HMENU)BTN_PREV, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Play/Pause", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        100, 30, 80, 30, MediaController, (HMENU)BTN_PLAYPAUSE, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Next", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        190, 30, 80, 30, MediaController, (HMENU)BTN_NEXT, hInstance, NULL);
	CreateWindow(L"BUTTON", L"ShowMenu", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 70, 80, 30, MediaController, (HMENU)BTN_POPUP, hInstance, NULL);

	FetchAudioOutputs();
    ShowWindow(MediaController, nCmdShow);
    UpdateWindow(MediaController);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
