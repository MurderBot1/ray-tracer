#include "user-input.h"

bool Input::s_Keys[512] = {};
bool Input::s_KeysPrev[512] = {};

void Input::Init()
{
    glfwSetKeyCallback(Window::GetGLFWWindow(), KeyboardCallback);
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
