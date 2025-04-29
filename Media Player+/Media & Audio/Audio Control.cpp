#include <Main.h>



// System Volume Control 
void SetSystemVolume(int volumePercent)
{
    if (g_SystemVolume) {
        float normalized = volumePercent / 100.0f;
        g_SystemVolume->SetMasterVolumeLevelScalar(normalized, NULL);
    }
}

// App Volume Control
void SetAppVolume(int sessionIndex, int volumePercent) {
    if (sessionIndex >= 0 && static_cast<size_t>(sessionIndex) < g_audioSessions.size()) {
        SessionInfo& session = g_audioSessions[sessionIndex];
        if (session.pSimpleAudioVolume) {
            float normalized = volumePercent / 100.0f;
            HRESULT hr = session.pSimpleAudioVolume->SetMasterVolume(normalized, NULL);
        }
    }
}
