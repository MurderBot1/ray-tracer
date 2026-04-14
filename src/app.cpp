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
    while (!glfwWindowShouldClose(Window::GetGLFWWindow()))
    {
        // Runs the loop which renders and displays a frame
        Loop();
    }

    // Cleans up app and saves log
    Cleanup();
}

void App::Setup()
{
    Window::Init();
    Audio::Init();

    // Set the first scene
    SetScene(Scene::FOREST);
}

void App::Loop()
{
    Input::NewFrame();
    glfwPollEvents();
    Window::DisplayFrame();
}

void App::Cleanup()
{
    Window::DestroyWindow();
    Audio::Cleanup();
}

void App::SetScene(Scene scene)
{
    if(gm_appRef->gm_scene == scene)
        return;
    gm_appRef->gm_scene = scene;

    Audio::SetScene(scene);
}