#pragma once
#include <fstream>
#include <cstddef>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>

constexpr std::size_t NUM_BUFFERS = 4;
constexpr ALsizei BUFFER_SIZE = 65536;

struct StreamingAudioData
{
    ALuint buffers[NUM_BUFFERS];
    std::string filename;
    std::ifstream file;
    std::uint8_t channels;
    std::int32_t sampleRate;
    std::uint8_t bitsPerSample;
    ALsizei size;
    ALuint source;
    ALsizei sizeConsumed = 0;
    ALenum format;
    OggVorbis_File oggVorbisFile;
    std::int_fast32_t oggCurrentSection = 0;
    std::size_t duration;
};
