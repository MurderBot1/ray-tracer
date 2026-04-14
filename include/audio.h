// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"
#include "scenes.h"

#include <map>
#include <iostream>

class Audio {
    public:
        /**
         * 
         */
        static void Init();
        
        /**
         * 
         */
        static void SetScene(Scene scene);
        
        /**
         * 
         */
        static void Cleanup();
    private:
        /**
         * 
         */
        static const std::map<Scene, const char*> getPaths();
    private:
        /// @brief 
        inline static ma_engine gm_engine;
        /// @brief
        inline static std::map<Scene, ma_sound> gm_audioMap;
};

#endif