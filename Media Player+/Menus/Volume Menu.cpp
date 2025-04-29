#include "Main.h"

HWND g_hwndSystemVolumeSlider = NULL;
HWND hwndVolumeMenu = NULL;
std::map<HWND, int> appVolumeTrackbars;

LRESULT CALLBACK PopupWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
    case WM_CREATE:
        return 0;
        
    case WM_HSCROLL:
        if ((HWND)lParam == g_hwndSystemVolumeSlider) {
            int volumePercent = SendMessage(g_hwndSystemVolumeSlider, TBM_GETPOS, 0, 0);
            SetSystemVolume(volumePercent);

            // Debug: Log system volume percentage
            wchar_t debugMessage[100];
            swprintf_s(debugMessage, L"System Volume Slider: %d%%\n", volumePercent);
            OutputDebugString(debugMessage);
        }
        else if (appVolumeTrackbars.find((HWND)lParam) != appVolumeTrackbars.end()) {
            int sessionIndex = appVolumeTrackbars[(HWND)lParam];
            int volumePercent = SendMessage((HWND)lParam, TBM_GETPOS, 0, 0);

            // Debug: Log app volume session index and percentage
            wchar_t debugMessage[200];
            swprintf_s(debugMessage, L"App Volume Slider:\nSession Index: %d\nVolume: %d%%\n", sessionIndex, volumePercent);
            OutputDebugString(debugMessage);

            SetAppVolume(sessionIndex, volumePercent);
        }
        return 0;
    case WM_KILLFOCUS:
        if (!IsChild(hwnd, (HWND)wParam)) {
            DestroyWindow(hwnd);
            hwndVolumeMenu = NULL;
        }
        return 0;

    case WM_DESTROY:
        hwndVolumeMenu = NULL;  
		ReleaseCapture();
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
       400, 400,    
       parentHwnd, NULL, wc.hInstance, NULL  
   );  
   g_hwndSystemVolumeSlider = CreateWindowEx(  
       WS_EX_CONTROLPARENT,  
       TRACKBAR_CLASS,  
       L"System Volume",  
       WS_CHILD | WS_VISIBLE | TBS_NOTICKS,   
       10, 10, 180, 30,  
       hwndVolumeMenu, NULL, wc.hInstance, NULL  
   );  
   SendMessage(g_hwndSystemVolumeSlider, TBM_SETRANGE, TRUE, MAKELPARAM(0, 100));

         appVolumeTrackbars.clear(); 
         for (size_t i = 0; i < g_audioSessions.size(); i++) {
             HWND hwndAppVolumeSlider = CreateWindowEx(
                 WS_EX_CONTROLPARENT,
                 TRACKBAR_CLASS,
                 L"App Volume",
                 WS_CHILD | WS_VISIBLE | TBS_NOTICKS,
                 10, 50 + (i * 40), 180, 30,
                 hwndVolumeMenu, NULL, wc.hInstance, NULL
             );
             SendMessage(hwndAppVolumeSlider, TBM_SETRANGE, TRUE, MAKELPARAM(0, 100));
             appVolumeTrackbars[hwndAppVolumeSlider] = i; // Explicit cast to int
         }
    
   if (hwndVolumeMenu) {  
       ShowWindow(hwndVolumeMenu, SW_SHOW);  
       SetForegroundWindow(hwndVolumeMenu);    
       UpdateWindow(hwndVolumeMenu);  
   }  
}