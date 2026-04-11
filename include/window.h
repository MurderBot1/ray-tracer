// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef WINDOW_H
#define WINDOW_H

#include "renderer.h"
#include "imgui.h"

/**
 * The window class is used to display the UI.
 * It takes in the input from the renderer and displays it to the user.
 */
class Window 
{
    public:
        /** 
         * The CreateWindow function creates and displays the window.
         */
        static void CreateWindow();

        /** 
         * The DisplayFrame function displays a renderer output to the frame.
         */
        static void DisplayFrame();
        static void DisplayFrame(const RendererOutput& input);

        /** 
         * The DestroyWindow function hides and cleans up the display window. 
         */
        static void DestroyWindow();
    private:
        static ImGuiIO* io;
        static bool show;
};

#endif