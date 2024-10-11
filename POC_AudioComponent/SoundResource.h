#ifndef SOUNDRESOURCE_H
#define SOUNDRESOURCE_H

#include <string>
#include <vector>
#include <fstream>

class SoundResource {
public:
    SoundResource();
    ~SoundResource();

    bool LoadFromFileOGG(const std::string& filepath);
    std::string filename;
    std::ifstream file;
    int32_t sampleRate;
    uint8_t channels;
    std::size_t duration;
private:
    std::vector<short> _audioData;
    std::string _fileName;
    int _sampleRate;               // Sampling rate of the audio file (e.g., 44100Hz)
    bool _mono;                 // Number of audio channels (1 = mono, 2 = stereo)
    int _totalSamples;             // Total number of samples in the audio data
};

#endif // SOUNDRESOURCE_H