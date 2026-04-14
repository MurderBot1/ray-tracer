// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <GLFW/glfw3.h>
#include "rt-window.h"
#include "app.h"

/**
 * 
 */
class Input
{
public:
    static void Init();

    static bool IsKeyDown(int key);
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    static void CheckSceneChanges();
    static void NewFrame();

private:
    static bool s_Keys[512];
    static bool s_KeysPrev[512];

    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif