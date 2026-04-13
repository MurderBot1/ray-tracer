#ifndef GLFW_WINDOW_WRAPPER_H
#define GLFW_WINDOW_WRAPPER_H

#include "glfw3.h"
#include "stb_image.h"

struct WindowData
{
    uint16_t width = 640;
    uint16_t height = 480;
    const char* title = "Ray Tracer";
    const char* imagePath = "assets/images/icon.png";
};

class GLFWWindowWrapper
{
    public:
        GLFWWindowWrapper();
        ~GLFWWindowWrapper();
        GLFWwindow* GetWindow();
        WindowData GetData();
    private:
        const WindowData c_data;
        GLFWwindow* m_window;
        GLFWimage* m_imageIcon;
};

#endif