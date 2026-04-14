#include "audio.h"

void Audio::Init()
{
    if(ma_engine_init(nullptr, &gm_engine) != MA_SUCCESS) {
        std::cout << "Failed to load audio engine!\n";
        exit(-1);
    }
 
    for (auto& [key, value] : getPaths()) 
    {
        ma_result result = ma_sound_init_from_file(&gm_engine, value, MA_SOUND_FLAG_DECODE, nullptr, nullptr, &gm_audioMap[key]);
        ma_sound_set_looping(&gm_audioMap[key], MA_TRUE);
        ma_sound_stop(&gm_audioMap[key]);

        if (result != MA_SUCCESS)
        {
            std::cout << "Failed to load the audio file: " << value << "\n";
            ma_engine_uninit(&gm_engine);
            exit(-1);
        }
    }

    std::cout << "Loaded audio engine and sounds\n";
}

void Audio::SetScene(Scene scene)
{
    ma_engine_stop(&gm_engine);
    ma_sound_start(&gm_audioMap[scene]);
}

void Audio::Cleanup()
{
    for (auto& [key, value] : gm_audioMap) 
    {
        ma_sound_uninit(&value);
    }

    ma_engine_uninit(&gm_engine);

    std::cout << "Cleaned audio engine and sounds\n";
}

const std::map<Scene, const char *> Audio::getPaths()
{
    return {
        {Scene::FOREST, "assets/audio/forest.wav"},
        {Scene::SPACE, "assets/audio/space.wav"},
    };
}
