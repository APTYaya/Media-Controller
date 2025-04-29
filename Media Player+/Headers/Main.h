#pragma once

// Libraries
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "comctl32.lib")

// Windows headers
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdlib.h>
#include <Psapi.h>

// Audio headers
#include <Audioclient.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h> // Ensure this header is included for IAudioEndPointVolume
#include <objbase.h>
#include <combaseapi.h>

// STL headers
#include <vector>
#include <map>
#include <string>

// Button IDs
#define BTN_PREV     1
#define BTN_PLAYPAUSE 2
#define BTN_NEXT     3
#define BTN_POPUP    4 

// Audio Session Info
#pragma once

struct SessionInfo {
   IAudioSessionControl* pSessionControl;
   ISimpleAudioVolume* pSimpleAudioVolume;
   HWND hwndAppVolumeSlider;
};

extern std::vector<SessionInfo> g_audioSessions;

// Global Variables
extern HWND g_hwndSystemVolumeSlider;
extern HWND hwndVolumeMenu;
extern std::map<HWND, int> appVolumeTrackbars;

// Pointers to Audio Interfaces
extern IAudioEndpointVolume* g_SystemVolume;

// Forward declaration of functions
extern void SendMediaKey(WORD keyCode);
extern void SetSystemVolume(int volumePercent);
extern void SetAppVolume(int sessionindex, int volumePercent);
extern void FetchAudioOutputs();
extern void VolumeMenu(HWND parentHwnd);

// Window Procedures 
extern LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK PopupWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
