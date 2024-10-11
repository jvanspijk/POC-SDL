#pragma once
#include <memory>
#include <vector>
#include "AudioChannel.h"
#include "OpenALPlayer.h"

constexpr uint8_t AMOUNT_OF_CHANNELS = 8;

class AudioManager {
public:
    AudioManager() {
        auto audioPlayer = std::make_shared<OpenALPlayer>(); //Should be IAudioPlayer and then injected

        for (int i = 0; i < 8; ++i) {
            channels[i] = std::make_shared<AudioChannel>(i, audioPlayer);
        }
    }

    void PlayChannel(int id, int loops);
    void StopChannel(int id);
    void PauseChannel(int id);
    void ChangePitch(int id, float pitchFactor);
    void ChangeSpeed(int id, float speedFactor);
    void ChangeVolume(int id, float volume);

private:
    std::shared_ptr<AudioChannel> channels[8];
};

