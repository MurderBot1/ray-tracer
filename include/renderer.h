// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <stdint.h>

/**
 * The color struct is a data structure that stores a R, G, and B value
 */
struct Color
{
    uint8_t R, G, B;
};

/**
 * The output object of the renderer class.
 */
struct RendererOutput
{
    /**
     * The rendered data that will be put on the display.
     */
    std::vector<Color> frame; 
};

/** 
 * The renderer class is used to take the objects from the scene and render them to pixels.
 */
class Renderer 
{
    public:
        /**
         * The render function is used to render the scene.
         */
        static RendererOutput Render();
};

#endif