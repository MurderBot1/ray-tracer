#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <GLFW/glfw3.h>
#include "rt-window.h"

class Input
{
public:
    static void Init();

    // Engine-facing API
    static bool IsKeyDown(int key);
    static bool IsKeyPressed(int key);   // pressed this frame (optional)
    static bool IsKeyReleased(int key);  // released this frame (optional)

    static void NewFrame(); // call once per frame

private:
    static bool s_Keys[512];
    static bool s_KeysPrev[512];

    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif