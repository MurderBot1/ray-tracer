// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef RENDERER_H
#define RENDERER_H

#include "glfw-window-wrapper.h"

/** 
 * The renderer class is used to take the objects from the scene and render them to pixels.
 */
class Renderer 
{
    public: 
        Renderer();
    public:
        static Renderer g_instance;
    private:
        GLFWWindowWrapper m_window;
};

#endif