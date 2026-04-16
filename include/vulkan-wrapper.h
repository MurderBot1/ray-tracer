// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef VULKAN_WRAPPER_H
#define VULKAN_WRAPPER_H

#include "vulkan_raii.hpp"
#include "GLFW/glfw3.h"

#include <iostream>

class VulkanWrapper {
    public:
        VulkanWrapper();
        ~VulkanWrapper();
    private: 
        void InitInstance();
        void InitDevice();
        void InitPhysicalDevice();
        bool IsDeviceAdiquite(vk::raii::PhysicalDevice const & physicalDevice);    
        void InitLogicalDevice();
        void SetupQueue();
    private:
        vk::raii::Context context;
        vk::raii::Instance instance = nullptr;
        vk::raii::PhysicalDevice physicalDevice = nullptr;
        vk::raii::Device device = nullptr;
        vk::raii::Queue graphicsQueue = nullptr;
    private:
        uint32_t graphicsIndex = 0;
};

#endif