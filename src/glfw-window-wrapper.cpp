// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#include "glfw-window-wrapper.h"

GLFWWindowWrapper::GLFWWindowWrapper()
    : m_window(nullptr)
{
    m_window = glfwCreateWindow(c_data.width, c_data.height, c_data.title, nullptr, nullptr);

    m_imageIcon.pixels = stbi_load(c_data.imagePath, &m_imageIcon.width, &m_imageIcon.height, 0, 4);
    if (m_imageIcon.pixels && m_window) {
        glfwSetWindowIcon(m_window, 1, &m_imageIcon);
    }
}

GLFWWindowWrapper::~GLFWWindowWrapper()
{
    if (m_imageIcon.pixels) stbi_image_free(m_imageIcon.pixels);
}

GLFWwindow *GLFWWindowWrapper::GetWindow()
{
    return m_window;
}

WindowData GLFWWindowWrapper::GetData()
{
    return c_data;
}