#pragma once
#include <fstream>
#include <cstddef>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>

constexpr std::size_t NUM_BUFFERS = 4;
constexpr ALsizei BUFFER_SIZE = 65536; //32kB
/// <summary>
/// Resource that holds buffers and file information.
/// </summary>
struct StreamingAudioData
{
    //buffers are loaded into as the previous one is playing. That�s how the streaming works, one buffer is handed off to OpenAL as the previous ones are having the next few milliseconds of audio provided.
    ALuint buffers[NUM_BUFFERS]; 

    //filename is the filename of the original.ogg file.This is used in case the file handle is lost, to continue streaming we need to know which file to re - open.
    std::string filename;

    //file is the file handle.
    std::ifstream file;

    //channels are populated when we load the .ogg file. These are needed by OpenAL in order to understand the data being passed to it in the buffers.
    std::uint8_t channels;

    //sampleRate is populated when we load the .ogg file. These are needed by OpenAL in order to understand the data being passed to it in the buffers.
    std::int32_t sampleRate;

    //bitsPerSample is populated when we load the .ogg file. These are needed by OpenAL in order to understand the data being passed to it in the buffers.
    std::uint8_t bitsPerSample;

    //Total size of the ogg file in bytes. Populated when the file is first loaded.
    ALsizei size;

    //The OpenAL Source that is generated to play the file. You set the gain and position of the file with this.
    ALuint source;

    //sizeConsumed is used by the callbacks to understand where in the audio data that playback is up to.
    ALsizei sizeConsumed = 0;

    //The OpenAL enum of either MONO or STEREO
    ALenum format;

    //oggVoribsFile is a handle needed by Ogg Vorbis library.
    OggVorbis_File oggVorbisFile;

    //oggCurrentSection is the part of the audio that�s currently being played back.
    std::int_fast32_t oggCurrentSection = 0;

    //The total length of the audio data.
    std::size_t duration;
};
