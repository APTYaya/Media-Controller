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

/*void VolumeControl(int volume) {
	if (isSystemVolume) {
		SetSystemVolume(volume);
		}
	else if (isAppVolume) {
		SetAppVolume("Spotify.exe", volume);
	}
}


void SetSystemVolume(int volume) {
	// Implementation for setting system volume
}

void SetAppVolume(const char* appName, int volume) {
	// Implementation for settting app volume
}
*/