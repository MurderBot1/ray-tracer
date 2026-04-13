#include "glfw-window-wrapper.h"

GLFWWindowWrapper::GLFWWindowWrapper()
    : window(glfwCreateWindow(data.width, data.height, data.title, nullptr, nullptr))
{
}

GLFWwindow *GLFWWindowWrapper::GetWindow()
{
    return window;
}

WindowData GLFWWindowWrapper::GetData()
{
    return data;
}
