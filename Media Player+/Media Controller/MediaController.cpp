#include "Main.h"

bool isSystemVolume = false;
bool isAppVolume = false;

void SendMediaKey(WORD keyCode) {
	INPUT input = { 0 };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = keyCode;
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

int GetSystemVolume() {
	int volume = 50;
	return volume;
}

int GetAppVolume() {
	int volume = 50;
	return volume;
}


void VolumeControl(int volumePerecent) {
	if (isSystemVolume) {
		SetSystemVolume(volumePerecent);
	}
}

void SetSystemVolume(int volumePercent) {
	if (volumePercent < 0) volumePercent = 0;
	if (volumePercent > 100) volumePercent = 100;

	float normalizedVolume = volumePercent / 100.0f;

	if (normalizedVolume < 0.005f) {
		normalizedVolume = 0.0000f;
	}

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return;
	}

	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioEndpointVolume* pEndpointVolume = NULL;

	hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL,
		CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pEnumerator
	);
	if (SUCCEEDED(hr)) {
		hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	}
	if (SUCCEEDED(hr)) {
		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pEndpointVolume);
	}
	if (SUCCEEDED(hr)) {
		pEndpointVolume->SetMasterVolumeLevelScalar(normalizedVolume, NULL);
	}

	if (pEndpointVolume) pEndpointVolume->Release();
	if (pDevice) pDevice->Release();
	if (pEnumerator) pEnumerator->Release();
	CoUninitialize();
}

// Function to check if audio output devices are available
// Debugging Purpose keep for now 
void CheckAudioOutputDevices() {
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, _T("Failed to initialize COM library."), _T("Error"), MB_OK | MB_ICONERROR);
		return;
	}

	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;

	hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL,
		CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pEnumerator
	);

	if (SUCCEEDED(hr)) {
		hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
		if (SUCCEEDED(hr)) {
			MessageBox(NULL, _T("Audio output device found!"), _T("Success"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			MessageBox(NULL, _T("No audio output device found."), _T("Warning"), MB_OK | MB_ICONWARNING);
		}
	}
	else {
		MessageBox(NULL, _T("Failed to create device enumerator."), _T("Error"), MB_OK | MB_ICONERROR);
	}

	if (pDevice) pDevice->Release();
	if (pEnumerator) pEnumerator->Release();
	CoUninitialize();
}