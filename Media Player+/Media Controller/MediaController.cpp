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


// Placeholder function for Volume Control
void VolumeControl(int volume) {

	wprintf(L"Volume control: %d\n", volume);

	if (isSystemVolume) {
		wprintf(L"Adjusting system volume to: %d\n", volume);
		
	}
	else if (isAppVolume) {
		wprintf(L"Adjusting app volume to: %d\n", volume);
		
	}
}
/*void VolumeControl(int volume) {
	if (isSystemVolume) {
		SetSystemVolume(volume);
		}
	else if (isAppVolume) {
		SetAppVolume("Spotify.exe", volume);
	}
}


void SetSystemVolume(float volume) {
	IMMDeviceEnumerator* pEnumerator = nullptr;
	IMMDevice* pDevice = nullptr;
	IAudioEndpointVolume* pVolume = nullptr;
	
	



	



}

void SetAppVolume(const char* appName, int volume) {
	
}
*/