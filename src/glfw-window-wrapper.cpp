#include "glfw-window-wrapper.h"

GLFWWindowWrapper::GLFWWindowWrapper()
    : m_window(glfwCreateWindow(c_data.width, c_data.height, c_data.title, nullptr, nullptr))
{
}

GLFWwindow *GLFWWindowWrapper::GetWindow()
{
    return m_window;
}

WindowData GLFWWindowWrapper::GetData()
{
    return c_data;
}
