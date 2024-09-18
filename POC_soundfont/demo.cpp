#include <fluidsynth.h>
#include <rtmidi/RtMidi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//You will have to download your own soundfonts
const char* const SOUNDFONT_FILE_PATH = "Pokemon_GBA.sf2";

//Choices included are UN_Owen_Was_Her.mid and It_Has_To_Be_This_Way.mid
const char* const MIDI_FILE_PATH = "UN_Owen_Was_Her.mid";

// Helper function to load MIDI file into memory
std::vector<unsigned char> loadMidiFile(const std::string& midiFilePath) {
    std::ifstream file(midiFilePath, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Could not open MIDI file.");
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        throw std::runtime_error("Failed to read MIDI file.");
    }

    return buffer;
}

// MIDI message callback (for debugging or handling real-time input)
void midiCallback(double deltatime, std::vector<unsigned char> *message, void *userData) {
    std::cout << "Received MIDI message:";
    for (auto byte : *message) {
        std::cout << " " << static_cast<int>(byte);
    }
    std::cout << std::endl;
}

int main() {
    // Initialize the synthesizer settings
    fluid_settings_t* settings = new_fluid_settings();

    // Create the synthesizer
    fluid_synth_t* synth = new_fluid_synth(settings);

    // Load the SoundFont (replace "soundfont.sf2" with your actual SoundFont path)
    int sf_id = fluid_synth_sfload(synth, SOUNDFONT_FILE_PATH, 1);
    if (sf_id == FLUID_FAILED) {
        printf("Failed to load the SoundFont!\n");
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
        return 1;
    }

    // Create an audio driver (connects the synthesizer to the audio output)
    fluid_audio_driver_t* adriver = new_fluid_audio_driver(settings, synth);

    // Create a new MIDI player
    fluid_player_t* player = new_fluid_player(synth);

    // Load the MIDI file (replace "example.mid" with your MIDI file path)
    if (fluid_player_add(player, MIDI_FILE_PATH) != FLUID_OK) {
        printf("Failed to load MIDI file!\n");
        delete_fluid_player(player);
        delete_fluid_audio_driver(adriver);
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
        return 1;
    }

    // Play the MIDI file
    fluid_player_play(player);

    // Wait until the playback is finished
    while (fluid_player_get_status(player) == FLUID_PLAYER_PLAYING) {
        fluid_synth_write_s16(synth, 0, NULL, 0, 0, NULL, 0, 0);
    }

    // Clean up
    delete_fluid_player(player);
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);

    return 0;
}
