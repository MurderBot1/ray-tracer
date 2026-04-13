// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "app.h"

App* App::gm_appRef;

void App::RequestAppStop()
{
    // Request an app stop
    gm_appRef->m_running = false;
}

App::App()
{
    // Set the app reference which allows us to access it in a static way
    gm_appRef = this;
    
    // Runs setup which inits window
    Setup();

    // Runs the app until it is told to stop
    while (m_running)
    {
        // Runs the loop which renders and displays a frame
        Loop();
    }

    // Cleans up app and saves log
    Cleanup();
}

void App::Setup()
{
    Window::CreateWindow();
}

void App::Loop()
{
    Window::DisplayFrame();
}

void App::Cleanup()
{
    Window::DestroyWindow();
}
