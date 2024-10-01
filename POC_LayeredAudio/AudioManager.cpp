#include "AudioManager.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>
#include <iostream>
#include <fstream>
#include <vector>

AudioManager::AudioManager() {
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open audio device." << std::endl;
        return;
    }
    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    alGenSources(1, &baseSource);
    alGenSources(1, &intensitySource);

    isPlaying = false;
    currentPlaybackSpeed = 1.0f;
}

AudioManager::~AudioManager() {
    alDeleteSources(1, &baseSource);
    alDeleteSources(1, &intensitySource);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void AudioManager::LoadBuffer(ALuint& buffer, const std::string& filename) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename.c_str(), "rb");
    if (err != 0 || !file) {
        std::cerr << "Failed to open OGG file: " << filename << std::endl;
        return;
    }

    OggVorbis_File oggFile;
    if (ov_open(file, &oggFile, nullptr, 0) < 0) {
        std::cerr << "Failed to read OGG file: " << filename << std::endl;
        fclose(file);
        return;
    }

    vorbis_info* vorbisInfo = ov_info(&oggFile, -1);
    int channels = vorbisInfo->channels;
    int sampleRate = vorbisInfo->rate;

    std::vector<char> audioData;
    const int BUFFER_SIZE = 4096; 
    char buff[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = ov_read(&oggFile, buff, BUFFER_SIZE, 0, 2, 1, nullptr)) > 0) {
        audioData.insert(audioData.end(), buff, buff + bytesRead);
    }

    alGenBuffers(1, &buffer);
    alBufferData(buffer, channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
        audioData.data(), audioData.size(), sampleRate);

    ov_clear(&oggFile);
    fclose(file);
}

void AudioManager::loadMusic(const std::string& baseTrack, const std::string& intensityTrack) {
    LoadBuffer(baseBuffer, baseTrack);
    LoadBuffer(intensityBuffer, intensityTrack);

    alSourcei(baseSource, AL_BUFFER, baseBuffer);
    alSourcei(intensitySource, AL_BUFFER, intensityBuffer);
    alSourcei(baseSource, AL_LOOPING, AL_TRUE);
    alSourcei(intensitySource, AL_LOOPING, AL_TRUE);
}

void AudioManager::playMusic() {
    alSourcePlay(baseSource);
    alSourcePlay(intensitySource);
    std::cout << "playing music" << std::endl;
    isPlaying = true;
}

void AudioManager::pauseMusic() {
    alSourcePause(baseSource);
    alSourcePause(intensitySource);
    std::cout << "pausing music" << std::endl;
    isPlaying = false;
}

void AudioManager::stopMusic() {
    alSourceStop(baseSource);
    alSourceStop(intensitySource);
    isPlaying = false;
}

void AudioManager::setVolume(float volumeBase, float volumeIntensity) {
    alSourcef(baseSource, AL_GAIN, volumeBase);
    alSourcef(intensitySource, AL_GAIN, volumeIntensity);
    std::cout << "Set volume to: " << volumeBase << ", " << volumeIntensity << std::endl;
}

void AudioManager::setSpeed(float speedMultiplier) {
    currentPlaybackSpeed = speedMultiplier;
    alSourcef(baseSource, AL_PITCH, currentPlaybackSpeed);
    alSourcef(intensitySource, AL_PITCH, currentPlaybackSpeed);
}
