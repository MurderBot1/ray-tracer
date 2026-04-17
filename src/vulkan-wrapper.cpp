#include "vulkan-wrapper.h"

VulkanWrapper::VulkanWrapper()
{
    InitInstance();
    InitDevice();
    InitQueue();
    InitSurface();
    InitSwapChain();
    InitImageViews();
    InitGraphicsPipeline();
    std::cout << "Init vulkan\n";
}

VulkanWrapper::~VulkanWrapper()
{
}

std::vector<const char *> GetRequiredDeviceExtension()
{
    return { vk::KHRSwapchainExtensionName };
};

void VulkanWrapper::InitInstance()
{
    vk::ApplicationInfo appInfo = vk::ApplicationInfo()
                                      .setApiVersion(vk::ApiVersion14)
                                      .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
                                      .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
                                      .setPApplicationName("Ray Tracer")
                                      .setPEngineName("Ray Tracer Engine");

    // Get the required instance extensions from GLFW.
    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Check if the required GLFW extensions are supported by the Vulkan implementation.
    auto extensionProperties = context.enumerateInstanceExtensionProperties();
    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        if (std::ranges::none_of(extensionProperties,
                                 [glfwExtension = glfwExtensions[i]](auto const &extensionProperty)
                                 { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
        {
            std::cout << "Required GLFW extension not supported: " << std::string(glfwExtensions[i]) << "\n";
            exit(-1);
        }
    }

    vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo()
                                            .setPApplicationInfo(&appInfo)
                                            .setEnabledExtensionCount(glfwExtensionCount)
                                            .setPpEnabledExtensionNames(glfwExtensions);

    instance = vk::raii::Instance(context, createInfo);
}

void VulkanWrapper::InitDevice()
{
    InitPhysicalDevice();
    InitLogicalDevice();
}

void VulkanWrapper::InitPhysicalDevice()
{
    std::vector<vk::raii::PhysicalDevice> physicalDevices = instance.enumeratePhysicalDevices();
    auto const devIter = std::ranges::find_if(physicalDevices, [&](auto const &physicalDevice)
                                              { return IsDeviceAdiquite(physicalDevice); });
    if (devIter == physicalDevices.end())
    {
        std::cout << "Failed to find a adiquite GPU\n";
        exit(-1);
    }
    physicalDevice = *devIter;
}

bool VulkanWrapper::IsDeviceAdiquite(vk::raii::PhysicalDevice const &physicalDevice)
{
    // Check if it supports a valid pipeline
    bool pipelineSupport = physicalDevice.getProperties().apiVersion >= vk::ApiVersion14;

    // Check if any of the queue families support graphics operations
    auto queueFamilies = physicalDevice.getQueueFamilyProperties();
    bool supportsGraphics = std::ranges::any_of(queueFamilies, [](auto const &qfp)
                                                { return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics); });

    // Check if all required physicalDevice extensions are available
    auto availableDeviceExtensions = physicalDevice.enumerateDeviceExtensionProperties();
    bool supportsAllRequiredExtensions =
        std::ranges::all_of(GetRequiredDeviceExtension(),
                            [&availableDeviceExtensions](auto const &requiredDeviceExtension)
                            {
                                return std::ranges::any_of(availableDeviceExtensions,
                                                           [requiredDeviceExtension](auto const &availableDeviceExtension)
                                                           { return strcmp(availableDeviceExtension.extensionName, requiredDeviceExtension) == 0; });
                            });

    // Check if the physicalDevice supports the required features (dynamic rendering and extended dynamic state)
    auto features =
        physicalDevice
            .template getFeatures2<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan13Features, vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();
    bool supportsRequiredFeatures = features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
                                    features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

    // Return true if the physicalDevice meets all the criteria
    return pipelineSupport && supportsGraphics && supportsAllRequiredExtensions && supportsRequiredFeatures;
}

void VulkanWrapper::InitLogicalDevice()
{
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

    // get the first index into queueFamilyProperties which supports both graphics and present
    uint32_t queueIndex = 0;
    for (uint32_t qfpIndex = 0; qfpIndex < queueFamilyProperties.size(); qfpIndex++)
    {
        if ((queueFamilyProperties[qfpIndex].queueFlags & vk::QueueFlagBits::eGraphics) &&
            physicalDevice.getSurfaceSupportKHR(qfpIndex, *surface))
        {
            // found a queue family that supports both graphics and present
            queueIndex = qfpIndex;
            break;
        }
    }
    if (queueIndex == 0)
    {
        std::cout << "Could not find a queue for graphics and present -> terminating\n";
        exit(-1);
    }

    float queuePriority = 0.5f;

    vk::DeviceQueueCreateInfo deviceQueueCreateInfo = vk::DeviceQueueCreateInfo()
                                                          .setQueueFamilyIndex(graphicsIndex)
                                                          .setQueueCount(1)
                                                          .setPQueuePriorities(&queuePriority);

    // Create a chain of feature structures
    vk::StructureChain<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan14Features, vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT> featureChain = {
        vk::PhysicalDeviceFeatures2(),
        vk::PhysicalDeviceVulkan14Features()
            .setDynamicRenderingLocalRead(true),
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT()
            .setExtendedDynamicState(true)};

    std::vector<const char *> requiredDeviceExtension = GetRequiredDeviceExtension();

    vk::DeviceCreateInfo deviceCreateInfo = vk::DeviceCreateInfo()
                                                .setPNext(&featureChain.get<vk::PhysicalDeviceFeatures2>())
                                                .setQueueCreateInfoCount(1)
                                                .setQueueCreateInfos(deviceQueueCreateInfo)
                                                .setEnabledExtensionCount(static_cast<uint32_t>(requiredDeviceExtension.size()))
                                                .setPpEnabledExtensionNames(requiredDeviceExtension.data());

    device = vk::raii::Device(physicalDevice, deviceCreateInfo);
}

void VulkanWrapper::InitQueue()
{
    graphicsQueue = vk::raii::Queue(device, graphicsIndex, 0);
}

void VulkanWrapper::InitSurface()
{
    VkSurfaceKHR _surface;
    if (glfwCreateWindowSurface(*instance, Window::GetGLFWWindow(), nullptr, &_surface) != 0)
    {
        std::cout << "failed to create surface from GLFW\n";
        exit(-1);
    }
    surface = vk::raii::SurfaceKHR(instance, _surface);
}

void VulkanWrapper::InitSwapChain()
{
    vk::SurfaceCapabilitiesKHR surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(*surface);
    swapChainExtent = ChooseSwapExtent(surfaceCapabilities);
    uint32_t minImageCount = ChooseSwapMinImageCount(surfaceCapabilities);

    std::vector<vk::SurfaceFormatKHR> availableFormats = physicalDevice.getSurfaceFormatsKHR(*surface);
    swapChainSurfaceFormat = ChooseSwapSurfaceFormat(availableFormats);

    std::vector<vk::PresentModeKHR> availablePresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

    vk::SwapchainCreateInfoKHR swapChainCreateInfo = vk::SwapchainCreateInfoKHR()
                                                         .setSurface(surface)
                                                         .setMinImageCount(minImageCount)
                                                         .setImageFormat(swapChainSurfaceFormat.format)
                                                         .setImageColorSpace(swapChainSurfaceFormat.colorSpace)
                                                         .setImageExtent(swapChainExtent)
                                                         .setImageArrayLayers(1)
                                                         .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
                                                         .setImageSharingMode(vk::SharingMode::eExclusive)
                                                         .setPreTransform(surfaceCapabilities.currentTransform)
                                                         .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
                                                         .setPresentMode(ChooseSwapPresentMode(availablePresentModes))
                                                         .setClipped(true);

    swapChain = vk::raii::SwapchainKHR(device, swapChainCreateInfo);
    swapChainImages = swapChain.getImages();
}

void VulkanWrapper::InitImageViews()
{
    assert(swapChainImageViews.empty());

    vk::ImageViewCreateInfo imageViewCreateInfo = vk::ImageViewCreateInfo()
        .setViewType(vk::ImageViewType::e2D)
        .setFormat(swapChainSurfaceFormat.format)
        .setSubresourceRange({ vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 });
        
    for (auto &image : swapChainImages)
    {
        imageViewCreateInfo.image = image;
        swapChainImageViews.emplace_back( device, imageViewCreateInfo );
    }
}

void VulkanWrapper::InitGraphicsPipeline()
{
}

vk::Extent2D VulkanWrapper::ChooseSwapExtent(vk::SurfaceCapabilitiesKHR const &capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }
    int width, height;
    glfwGetFramebufferSize(Window::GetGLFWWindow(), &width, &height);

    return {
        std::clamp<uint32_t>(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
        std::clamp<uint32_t>(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height)};
}

uint32_t VulkanWrapper::ChooseSwapMinImageCount(vk::SurfaceCapabilitiesKHR const &surfaceCapabilities)
{
    auto minImageCount = std::max(3u, surfaceCapabilities.minImageCount);
    if ((0 < surfaceCapabilities.maxImageCount) && (surfaceCapabilities.maxImageCount < minImageCount))
    {
        minImageCount = surfaceCapabilities.maxImageCount;
    }
    return minImageCount;
}

vk::SurfaceFormatKHR VulkanWrapper::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats)
{
    const auto formatIt = std::ranges::find_if(
        availableFormats,
        [](const auto &format)
        { return format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear; });
    return formatIt != availableFormats.end() ? *formatIt : availableFormats[0];
}

vk::PresentModeKHR VulkanWrapper::ChooseSwapPresentMode(std::vector<vk::PresentModeKHR> const &availablePresentModes)
{
    assert(std::ranges::any_of(availablePresentModes, [](auto presentMode)
                               { return presentMode == vk::PresentModeKHR::eFifo; }));
    return std::ranges::any_of(availablePresentModes,
                               [](const vk::PresentModeKHR value)
                               { return vk::PresentModeKHR::eMailbox == value; })
               ? vk::PresentModeKHR::eMailbox
               : vk::PresentModeKHR::eFifo;
}