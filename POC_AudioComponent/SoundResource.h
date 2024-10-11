#ifndef SOUNDRESOURCE_H
#define SOUNDRESOURCE_H

#include <string>
#include <vector>

class SoundResource {
public:
    SoundResource();
    ~SoundResource();

    bool LoadFromFileOGG(const std::string& filepath);

    const std::vector<short>& GetAudioData() const { return _audioData; }
    int GetSampleRate() const { return _sampleRate; }
    int GetChannels() const { return _mono ? 1 : 2; }
    int GetTotalSamples() const { return _totalSamples; }

private:
    std::vector<short> _audioData;
    std::string _fileName;
    int _sampleRate;               // Sampling rate of the audio file (e.g., 44100Hz)
    bool _mono;                 // Number of audio channels (1 = mono, 2 = stereo)
    int _totalSamples;             // Total number of samples in the audio data
};

#endif // SOUNDRESOURCE_H