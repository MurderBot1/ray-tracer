// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "app.h"

App* App::appRef;

void App::RequestAppStop()
{
    // Request an app stop
    appRef->running = false;
}

App::App()
{
    // Set the app reference which allows us to access it in a static way
    appRef = this;
    
    // Runs setup which inits window
    Setup();

    // Runs the app until it is told to stop
    while (running)
    {
        // Runs the loop which renders and displays a frame
        Loop();
    }

    // Cleans up app and saves log
    Cleanup();
}

void App::Setup()
{
}

void App::Loop()
{
}

void App::Cleanup()
{
}
