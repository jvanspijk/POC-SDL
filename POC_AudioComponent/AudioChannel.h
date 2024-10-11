#pragma once
#include <vector>
#include <memory>
#include "SoundResource.h"
#include "IAudioPlayer.h"

class AudioChannel
{
public:
    AudioChannel(int id, std::shared_ptr<IAudioPlayer> audioPlayer)
        : _id(id), _isPlaying(false), _pitch(1.0f), _playbackSpeed(1.0f), _audioPlayer(audioPlayer) {}

    void Play(int loops);
    void Stop();
    void Pause();
    void ChangePitch(float pitchFactor);
    void ChangeSpeed(float speedFactor);
    void ChangeVolume(float volume);

    bool IsPlaying() const { return _isPlaying; }
    int GetId() const { return _id; }

private:
    int _id;
    bool _isPlaying;
    std::vector<std::shared_ptr<SoundResource>> _layers;
    float _pitch;
    float _playbackSpeed;
    std::shared_ptr<IAudioPlayer> _audioPlayer;
};

