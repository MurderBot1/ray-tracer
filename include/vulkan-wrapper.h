// Copyright © 2026 Trent Cridland. All rights reserved. Contact me at murderbot1@outlook.com
#ifndef VULKAN_WRAPPER_H
#define VULKAN_WRAPPER_H

// #define VULKAN_HPP_NO_CONSTRUCTORS
// #define VULKAN_HPP_NO_EXCEPTIONS
// #define VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL 1
// #define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1

#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan_raii.hpp"
#include "GLFW/glfw3.h"
#include "rt-window.h"

#include <iostream>

class VulkanWrapper {
    public:
        VulkanWrapper();
        ~VulkanWrapper();
    private: 
        void InitInstance();
        void InitDevice();
        void InitPhysicalDevice();
        void InitLogicalDevice();
        void InitQueue();
        void InitSurface();
        void InitSwapChain();
        void InitImageViews();
        void InitGraphicsPipeline();
    private:
        bool IsDeviceAdiquite(vk::raii::PhysicalDevice const & physicalDevice);    
        vk::Extent2D ChooseSwapExtent(vk::SurfaceCapabilitiesKHR const &capabilities);
        uint32_t ChooseSwapMinImageCount(vk::SurfaceCapabilitiesKHR const &surfaceCapabilities);
        vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
        vk::PresentModeKHR ChooseSwapPresentMode(std::vector<vk::PresentModeKHR> const &availablePresentModes);
    private:
        vk::raii::Context context;
        vk::raii::Instance instance = nullptr;
        vk::raii::PhysicalDevice physicalDevice = nullptr;
        vk::raii::Device device = nullptr;
        vk::raii::Queue graphicsQueue = nullptr;
        vk::raii::SurfaceKHR surface = nullptr;
        vk::Extent2D swapChainExtent;
        vk::SurfaceFormatKHR swapChainSurfaceFormat;
        vk::raii::SwapchainKHR swapChain = nullptr;
        std::vector<vk::Image> swapChainImages;
        std::vector<vk::raii::ImageView> swapChainImageViews;
    private:
        uint32_t graphicsIndex = 0;
};

#endif