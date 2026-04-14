// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef GLFW_WINDOW_WRAPPER_H
#define GLFW_WINDOW_WRAPPER_H

#include "GLFW/glfw3.h"
#include "stb_image.h"

/**
 * 
 */
struct WindowData
{
    /// @brief
    uint16_t width = 640;
    /// @brief
    uint16_t height = 480;
    /// @brief
    const char* title = "Ray Tracer";
    /// @brief
    const char* imagePath = "assets/images/icon.png";
};

/**
 * 
 */
class GLFWWindowWrapper
{
    public:
        /**
         * 
         */
        GLFWWindowWrapper();
        
        /**
         * 
         */
        ~GLFWWindowWrapper();
        
        /**
         * 
         */
        GLFWwindow* GetWindow();
        
        /**
         * 
         */
        WindowData GetData();
    private:
        /// @brief 
        const WindowData c_data;
        /// @brief
        GLFWwindow* m_window;
        /// @brief
        GLFWimage m_imageIcon;
};

#endif