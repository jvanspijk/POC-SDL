#pragma once
#include <string>
#include "OpenALAudioResource.h"
#include "IAudioPlayer.h"

class OpenALPlayer : public IAudioPlayer
{
public:
    OpenALPlayer();
    ~OpenALPlayer();

    bool Load(const std::string& filepath) override;
    void Play(int loops) override;
    void Stop() override;
    void Pause() override;
    void ChangePitch(float pitchFactor) override;
    void ChangeSpeed(float speedFactor) override;
    void Update();

private:
    OpenALAudioResource _audioData;
    bool create_stream_from_file(const std::string& filename, OpenALAudioResource& audioData);
    void play_stream(const OpenALAudioResource& audioData);
    void update_stream(OpenALAudioResource& audioData);
    void stop_stream(const OpenALAudioResource& audioData);

    //Should maybe be in the manager instead
    ALCdevice* _device;
    ALCcontext* _context;

    //The following functions will act as wrappers around any OpenAL function calls and automatically check for errors.
    #define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)
    #define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)

    void check_al_errors(const std::string& filename, const std::uint_fast32_t line);

    template<typename alFunction, typename... Params>
    auto alCallImpl(const char* filename, const std::uint_fast32_t line, alFunction function, Params... params)
        -> typename std::enable_if<std::is_same<void, decltype(function(params...))>::value, decltype(function(params...))>::type
    {
        function(std::forward<Params>(params)...);
        check_al_errors(filename, line);
    }

    template<typename alFunction, typename... Params>
    auto alCallImpl(const char* filename, const std::uint_fast32_t line, alFunction function, Params... params)
        -> typename std::enable_if<!std::is_same<void, decltype(function(params...))>::value, decltype(function(params...))>::type
    {
        auto ret = function(std::forward<Params>(params)...);
        check_al_errors(filename, line);
        return ret;
    }
};

