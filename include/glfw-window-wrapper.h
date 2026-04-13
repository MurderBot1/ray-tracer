#ifndef GLFW_WINDOW_WRAPPER_H
#define GLFW_WINDOW_WRAPPER_H

#include "glfw3.h"

struct WindowData
{
    uint16_t width = 640;
    uint16_t height = 480;
    const char* title = "Ray Tracer";
};

class GLFWWindowWrapper
{
    public:
        GLFWWindowWrapper();
        GLFWwindow* GetWindow();
        WindowData GetData();
    private:
        WindowData data;
        GLFWwindow* window;
};

#endif