#include "AudioManager.h"

void AudioManager::PlayChannel(int id, int loops) {
    if (id >= 0 && id < AMOUNT_OF_CHANNELS) {
        channels[id]->Play(loops);
    }
}

void AudioManager::StopChannel(int id) {
    if (id >= 0 && id < AMOUNT_OF_CHANNELS) {
        channels[id]->Stop();
    }
}

void AudioManager::PauseChannel(int id) {
    if (id >= 0 && id < AMOUNT_OF_CHANNELS) {
        channels[id]->Pause();
    }
}

void AudioManager::ChangePitch(int id, float pitchFactor) {
    if (id >= 0 && id < AMOUNT_OF_CHANNELS) {
        channels[id]->ChangePitch(pitchFactor);
    }
}

void AudioManager::ChangeSpeed(int id, float speedFactor) {
    if (id >= 0 && id < AMOUNT_OF_CHANNELS) {
        channels[id]->ChangeSpeed(speedFactor);
    }
}

void AudioManager::ChangeVolume(int id, float volume)
{
    if (id >= 0 && id < AMOUNT_OF_CHANNELS) {
        channels[id]->ChangeVolume(volume);
    }
}

void AudioManager::LoadFile(std::string path)
{
}
