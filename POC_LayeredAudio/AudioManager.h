#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class AudioManager {
public:
    AudioManager(int channels, int frequency);
    ~AudioManager();

    bool loadSoundEffect(const std::string& filePath, const std::string& id);
    void playSoundEffect(const std::string& id, int amountOfLoops);
    void fadeIn(const std::string& id, float fadeInSeconds);
    void fadeOut(const std::string& id, float fadeOutSeconds);
    void mute(const std::string& id);
    void close();
    std::map<std::string, int> playingChannels;

private:
    std::map<std::string, Mix_Chunk*> soundEffects;
    void fadeVolume(int channel, int startVolume, int endVolume, int fadeDurationSeconds);
};

#endif
