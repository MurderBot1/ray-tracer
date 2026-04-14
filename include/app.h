// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef APP_H
#define APP_H

#include "renderer.h"
#include "rt-window.h"
#include "scenes.h"
#include "audio.h"

/**
 * App is the main class that controls the program. It runs this in order:
 * 1. Starts up all parts of the program such as the display window.
 * 2. Runs the loops until running is set to false
 * 3. Runs the cleanup function which does simple cleanup tasks like saving files and shutting down the window.
 */
class App 
{
    public:
        /// @brief This is the function that allows us to request the app to stop in any part of the program.
        static void RequestAppStop();
    public:
        /**
         * The initilizer of App allows is used to setup and start running.
         * This is done so that we can call App(); in the main function to clean it up.
         */
        App();
    private:
        /**
         * The Setup function is ran once as the first thing that the program does.
         * The goal of this fucntion is to initilize variables and other classes that the progam needs.
         */
        void Setup();
        
        /**
         * The Loop function is ran once per frame.
         * The goal of this function is to render the scene and run things that need to be ran once per frame.
         */
        void Loop();
        
        /**
         * The Cleanup function is ran at the end of the program.
         * The goal of this function is to save log files and Cleanup other things used by the application.
         */
        void Cleanup();

        /**
         * The SetScene function allows you to switch the scene the app is displaying
         */
        static void SetScene(Scene scene);
    private:
        /// @brief This variable controls when the app is running.
        bool m_running = true;

        /// @brief The current loaded scene
        Scene gm_scene;
        
        /// @brief This variable stores the reference to the running app class allowing it to have static functions.
        static App* gm_appRef;
};

#endif