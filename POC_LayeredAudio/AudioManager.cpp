#include "AudioManager.h"
#include<SDL2/SDL.h>
#include <iostream>
#include <thread>

AudioManager::AudioManager(int channels, int frequency) {
    Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(channels);
}

AudioManager::~AudioManager() {
    close();
}

bool AudioManager::loadSoundEffect(const std::string& filePath, const std::string& id) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound effect: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundEffects[id] = sound;
    return true;
}

void AudioManager::playSoundEffect(const std::string& id, int loops) {
    if (soundEffects.find(id) != soundEffects.end()) {
        int channel = Mix_PlayChannel(-1, soundEffects[id], loops);
        playingChannels[id] = channel;
    }
}

void AudioManager::fadeIn(const std::string& id, int fadeInSeconds) {
    if (soundEffects.find(id) != soundEffects.end()) {
        int channel = playingChannels[id];

        Mix_Volume(channel, MIX_MAX_VOLUME);
        int fadeInMilliseconds = fadeInSeconds * 1000;
        Mix_FadeInChannel(channel, nullptr, -1, fadeInMilliseconds);
    }
}

void AudioManager::fadeOut(const std::string& id, int fadeOutSeconds) {
    if (soundEffects.find(id) != soundEffects.end()) {
        int channel = playingChannels[id];

        Mix_Volume(channel, 0);
        int fadeOutMilliseconds = fadeOutSeconds * 1000;
        Mix_FadeOutChannel(channel, fadeOutMilliseconds);
    }
}

void AudioManager::mute(const std::string& id) {
    if (playingChannels.find(id) != playingChannels.end()) {
        int channel = playingChannels[id];
        Mix_Volume(channel, 0);
    }
}

void AudioManager::close() {
    for (auto& pair : soundEffects) {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();
    Mix_CloseAudio();
}
