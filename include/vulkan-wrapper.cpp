#include "vulkan-wrapper.h"

VulkanWrapper::VulkanWrapper()
{
    InitInstance();
    InitDevice();
}

VulkanWrapper::~VulkanWrapper()
{
}

void VulkanWrapper::InitInstance()
{
    vk::ApplicationInfo appInfo = vk::ApplicationInfo()
        .setApiVersion(vk::ApiVersion14)
        .setApplicationVersion(VK_MAKE_VERSION( 1, 0, 0 ))
        .setEngineVersion(VK_MAKE_VERSION( 1, 0, 0 ))
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
                                [glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
                                { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
        {
            throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
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
    auto const devIter = std::ranges::find_if( physicalDevices, [&]( auto const & physicalDevice ) { return IsDeviceAdiquite( physicalDevice ); } );
    if ( devIter == physicalDevices.end() )
    {
        throw std::runtime_error( "failed to find a suitable GPU!" );
    }
    physicalDevice = *devIter;
}

bool VulkanWrapper::IsDeviceAdiquite(vk::raii::PhysicalDevice const &physicalDevice)
{
    // Check if it supports a valid pipeline
    bool pipelineSupport = physicalDevice.getProperties().apiVersion >= vk::ApiVersion14;

    // Check if any of the queue families support graphics operations
    auto queueFamilies    = physicalDevice.getQueueFamilyProperties();
    bool supportsGraphics = std::ranges::any_of( queueFamilies, []( auto const & qfp ) { return !!( qfp.queueFlags & vk::QueueFlagBits::eGraphics ); } );

    // Check if all required physicalDevice extensions are available
    std::vector<const char*> requiredDeviceExtension = {vk::KHRSwapchainExtensionName};
    auto availableDeviceExtensions = physicalDevice.enumerateDeviceExtensionProperties();
    bool supportsAllRequiredExtensions =
    std::ranges::all_of( requiredDeviceExtension,
                         [&availableDeviceExtensions]( auto const & requiredDeviceExtension )
                         {
                           return std::ranges::any_of( availableDeviceExtensions,
                                                       [requiredDeviceExtension]( auto const & availableDeviceExtension )
                                                       { return strcmp( availableDeviceExtension.extensionName, requiredDeviceExtension ) == 0; } );
                         } );

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
    auto graphicsQueueFamilyProperty = std::ranges::find_if(queueFamilyProperties, [](auto const &qfp) { return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0); });
    graphicsIndex = static_cast<uint32_t>(std::distance(queueFamilyProperties.begin(), graphicsQueueFamilyProperty));

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
            .setExtendedDynamicState(true)
    };
    
    std::vector<const char*> requiredDeviceExtension = {
        vk::KHRSwapchainExtensionName
    };

    vk::DeviceCreateInfo deviceCreateInfo = vk::DeviceCreateInfo()
        .setPNext(&featureChain.get<vk::PhysicalDeviceFeatures2>())
        .setQueueCreateInfoCount(1)
        .setQueueCreateInfos(deviceQueueCreateInfo)
        .setEnabledExtensionCount(static_cast<uint32_t>(requiredDeviceExtension.size()))
        .setPpEnabledExtensionNames(requiredDeviceExtension.data());

    device = vk::raii::Device( physicalDevice, deviceCreateInfo );
}

void VulkanWrapper::SetupQueue()
{
    graphicsQueue = vk::raii::Queue( device, graphicsIndex, 0 );
}
