#pragma once
#include <string>

class IAudioPlayer {
public:
    virtual ~IAudioPlayer() = default;

    virtual bool Load(const std::string& filepath) = 0;
    virtual void Play(int loops) = 0;
    virtual void Stop() = 0;
    virtual void Pause() = 0;
    virtual void ChangePitch(float pitchFactor) = 0;
    virtual void ChangeSpeed(float speedFactor) = 0;
};