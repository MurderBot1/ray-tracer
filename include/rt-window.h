// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef WINDOW_H
#define WINDOW_H

#include "renderer.h"
#include "imgui.h"
#include "glfw-window-wrapper.h"

#include <memory>

/**
 * The window class is used to display the UI.
 * It takes in the input from the renderer and displays it to the user.
 */
class Window 
{
    public:
        /** 
         * The Init function creates and displays the window.
         */
        static void Init();

        /** 
         * The DisplayFrame function displays a renderer output to the frame.
         */
        static void DisplayFrame();

        /** 
         * The DestroyWindow function hides and cleans up the display window. 
         */
        static void DestroyWindow();
    public:
        /**
         * 
         */
        static GLFWwindow* GetGLFWWindow();
    private:
        /// @brief
        static std::unique_ptr<Window> ref;
        /// @brief
        ImGuiIO* m_io;
        /// @brief
        bool m_showing;
        /// @brief
        GLFWWindowWrapper m_window;
};

#endif