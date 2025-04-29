#include "Main.h"

std::vector<SessionInfo> g_audioSessions;

IAudioEndpointVolume* g_SystemVolume = nullptr;

// Function to get process name from process ID
std::wstring GetProcessNameFromId(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess) {
        wchar_t processName[MAX_PATH] = L"<Unknown>";
        if (GetModuleBaseName(hProcess, NULL, processName, MAX_PATH)) {
            CloseHandle(hProcess);
            return std::wstring(processName);
        }
        CloseHandle(hProcess);
    }
    return L"<Unknown>";
}
// Fetching System volume and App Audio Session volume
void FetchAudioOutputs() {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        return;
    }

    // SYSTEM VOLUME SETUP  
    {
        IMMDeviceEnumerator* pEnumerator = NULL;
        IMMDevice* pDevice = NULL;

        if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator)))
            return;
        {
        if (FAILED(pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice)))
	        return;
             pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&g_SystemVolume);
            
        }
        // Clean up
		pDevice->Release();
		pEnumerator->Release();
    }

    // APP AUDIO SESSION VOLUME SETUP  
    {
        IMMDeviceEnumerator* pEnumerator = nullptr;
        IMMDevice* pDevice = nullptr;
        IAudioSessionManager2* pSessionManager = nullptr;
        IAudioSessionEnumerator* pSessionEnumerator = nullptr;

        g_audioSessions.clear();

        if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator)))
            return;

        if (FAILED(pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice)))
            return;

        if (FAILED(pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager)))
            return;

        if (FAILED(pSessionManager->GetSessionEnumerator(&pSessionEnumerator)))
            return;

        int sessionCount = 0;
        pSessionEnumerator->GetCount(&sessionCount);

        for (int i = 0; i < sessionCount; i++) {
            IAudioSessionControl* pSessionControl = nullptr;
            ISimpleAudioVolume* pSimpleAudioVolume = nullptr;

            if (SUCCEEDED(pSessionEnumerator->GetSession(i, &pSessionControl))) {
                if (SUCCEEDED(pSessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pSimpleAudioVolume))) {
                    SessionInfo sessionInfo = { pSessionControl, pSimpleAudioVolume };
                    g_audioSessions.push_back(sessionInfo);
                    wchar_t debugMessage[256];
                    swprintf_s(debugMessage, L"Session added: Total sessions=%zu\n", g_audioSessions.size());
                    OutputDebugString(debugMessage);

                    
                    DWORD processId = 0;
                    IAudioSessionControl2* pSessionControl2 = nullptr;
                    if (SUCCEEDED(pSessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**)&pSessionControl2))) {
                        if (SUCCEEDED(pSessionControl2->GetProcessId(&processId))) {
                            std::wstring processName = GetProcessNameFromId(processId);
                            wchar_t processMessage[256];
                            swprintf_s(processMessage, L"Session %d belongs to process ID: %lu (%s)\n", i, processId, processName.c_str());
                            OutputDebugString(processMessage);
                        }
                        pSessionControl2->Release();
                    }
                    
                }
                pSessionControl->Release();
			}
		}

    // Clean Up
    pSessionEnumerator->Release();
    pSessionManager->Release();
    pDevice->Release();
    pEnumerator->Release();
    }
    CoUninitialize();

}

