#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void loadMusic(const std::string& baseTrack, const std::string& intensityTrack);
    void playMusic();
    void pauseMusic();
    void stopMusic();

    void setVolume(float volumeBase, float volumeIntensity);
    void setSpeed(float speedMultiplier);
private:
    ALuint baseSource;         
    ALuint intensitySource;    
    ALuint baseBuffer;       
    ALuint intensityBuffer; 

    float currentPlaybackSpeed;        
    bool isPlaying;
    ALCdevice* device;         
    ALCcontext* context;      

    void LoadBuffer(ALuint& buffer, const std::string& filename);       
};
