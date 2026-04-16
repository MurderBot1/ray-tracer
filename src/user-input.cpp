// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "user-input.h"

bool Input::s_Keys[512] = {};
bool Input::s_KeysPrev[512] = {};

void Input::Init()
{
    glfwSetKeyCallback(Window::GetGLFWWindow(), KeyboardCallback);
    std::cout << "Loaded input engine\n";
}

void Input::CheckSceneChanges()
{
    if (IsKeyDown(GLFW_KEY_1))
    {
        App::SetScene(Scene::FOREST);
    }
    
    if (IsKeyDown(GLFW_KEY_2))
    {
        App::SetScene(Scene::SPACE);
    }
}

void Input::NewFrame()
{
    for (int i = 0; i < 512; i++)
        s_KeysPrev[i] = s_Keys[i];
}

void Input::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < 512)
        s_Keys[key] = (action != GLFW_RELEASE);
}

bool Input::IsKeyDown(int key)
{
    return s_Keys[key];
}

bool Input::IsKeyPressed(int key)
{
    return s_Keys[key] && !s_KeysPrev[key];
}

bool Input::IsKeyReleased(int key)
{
    return !s_Keys[key] && s_KeysPrev[key];
}
