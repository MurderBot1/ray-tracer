#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"
#include "scenes.h"

#include <map>
#include <iostream>

class Audio {
    public:
        void Init();
        void SetScene(Scene scene);
        void Cleanup();
    private:
        const std::map<Scene, const char*> getPaths();
    private:
        static ma_engine gm_engine;
        static std::map<Scene, ma_sound> gm_audioMap;
};

#endif