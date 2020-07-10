#include "Vulkan_RenderDevice.hpp"

#include <sstream>
#include <unordered_map>

#include "../Log.hpp"


/** Default Constructor */
Vulkan_RenderDevice::Vulkan_RenderDevice()
{

}

/** Internal Constructor */
Vulkan_RenderDevice::Vulkan_RenderDevice(
    const char* windowName)
{

    // Create Vulkan Instance //
    {
        vk::ApplicationInfo appInfo{ 
            "Chronos Application", 
            VK_MAKE_VERSION(0, 0, 1), 
            "Chronos Engine", 
            VK_MAKE_VERSION(0, 1, 2),
            VK_API_VERSION_1_2 };

        // Check validation layers
        std::vector<vk::LayerProperties> availableLayers;

        if(m_enableValidationLayers)
        {

            availableLayers = vk::enumerateInstanceLayerProperties();


            // Check all the layers in validation layer is in the available layers
            for(std::string validationLayer : m_validationLayers)
            {
                bool layerFound = false;

                for(vk::LayerProperties availableLayer : availableLayers)
                {
                    if(validationLayer == availableLayer.layerName)
                    {
                        layerFound = true;
                        break; // Layer found!
                    }
                }

                if(!layerFound)
                {
                    // Since we cant get validation layers we should just keep running they dont effect gameplay
                    m_validationLayersSupported = false;
                    Log::LogError("Vulkan Render Device", "Could not find a validation layer!");
                }
            }
        }

        // Get the instance extensions
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if(m_enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        vk::InstanceCreateInfo instanceCreateInfo(
            {},
            &appInfo,
#ifdef NDEBUG
            0,
            nullptr,
#else
            (uint32_t)m_validationLayers.size(),
            m_validationLayers.data(),
#endif
            (uint32_t)extensions.size(),
            extensions.data()
        );

        m_vkInstance = vk::createInstance(instanceCreateInfo);
    }

    // Setup debug messenger
    {
        m_vkDispatchLoader = vk::DispatchLoaderDynamic(m_vkInstance, vkGetInstanceProcAddr);

        if(m_enableValidationLayers)
        {
            auto severityFlags = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
                        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo;

            auto typeFlags = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                            | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                            | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;

            m_vkDebugMessenger = m_vkInstance.createDebugUtilsMessengerEXT(
                {{}, severityFlags, typeFlags, debugCallback},
                nullptr,
                m_vkDispatchLoader);
        }
    }

    // Pick physical device
    {
        // Find all physical devices that support vulkan
         std::vector<vk::PhysicalDevice> physicalDevices = m_vkInstance.enumeratePhysicalDevices(m_vkDispatchLoader);
    
        if(physicalDevices.size() == 0)
            Log::LogError("Vulkan Render Device", "Could not find a GPU with vulkan support!");
    
        std::unordered_map<float, vk::PhysicalDevice> gpuChoices;

        vk::PhysicalDevice bestPhysicalDevice;
        float bestScore = 0;

        // Find the highest scored GPU and use that for the default GPU
        for(const vk::PhysicalDevice& device : physicalDevices)
        {
            // To calculate the scores of device you just need to add up all of the information

            // Memory

            uint64_t gpuScore = 0;

            // Memory Score
            {
                vk::PhysicalDeviceMemoryProperties2 memoryProperties = device.getMemoryProperties2(m_vkDispatchLoader);

                for(vk::MemoryHeap heap : memoryProperties.memoryProperties.memoryHeaps)
                    gpuScore += (uint32_t)heap.size; /// 2; // Dividing because if a gpu has too much ram
            }
            
            // Features Score
            {
                vk::PhysicalDeviceProperties2 deviceProperties;
                deviceProperties = device.getProperties2(m_vkDispatchLoader);

                vk::PhysicalDeviceFeatures2 deviceFeatures;
                deviceFeatures = device.getFeatures2(m_vkDispatchLoader);

                if(deviceProperties.properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
                    gpuScore += 1000; // No internal gpu should have a higher score than a discrete gpu

                gpuScore += deviceProperties.properties.limits.maxImageArrayLayers;
                gpuScore += deviceProperties.properties.limits.maxImageDimension2D;
                gpuScore += deviceProperties.properties.limits.maxMemoryAllocationCount;
                gpuScore += deviceProperties.properties.limits.maxPerStageResources;
                gpuScore += (uint32_t)deviceProperties.properties.limits.maxSamplerAnisotropy;
                gpuScore += deviceProperties.properties.limits.maxGeometryOutputVertices;

                // Max score is supposed to be the theoretical best GPU on the market
                // If anyone gets greater than %100 you should fix this and make it your number
                const uint64_t maxScore = 15000000000; // I used this number because it makes my RTX 2070 look better (it will change)

                // Calculate a normalized score
                float normalizedScore = (float)gpuScore / (float)maxScore;
                normalizedScore *= 100;
                
                // Change the precision of the normalized score so we only get one decimal point
                std::ostringstream normalizedScoreString;
                normalizedScoreString.precision(1);
                normalizedScoreString << std::fixed << normalizedScore;

                if(normalizedScore > bestScore)
                    bestPhysicalDevice = device;

                gpuChoices.insert(std::pair<float, vk::PhysicalDevice>(normalizedScore, device));
                Log::LogMessage("Vulkan Render Device", std::string(deviceProperties.properties.deviceName) +  " got a score of %" + normalizedScoreString.str());
            }
        }

        // Get the highest scored device and use it
        m_vkPhysicalDevice = bestPhysicalDevice;
    }

    // Find Queue families
    {
        QueueFamilyIndices* indices = new QueueFamilyIndices();

        std::vector<vk::QueueFamilyProperties> queueFamilies = m_vkPhysicalDevice.getQueueFamilyProperties(m_vkDispatchLoader);

        int i = 0;
        for(const vk::QueueFamilyProperties queueFamily : queueFamilies)
        {
            if(queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
                indices->graphicsFamily = std::pair<uint32_t, bool>(i, true); // We have a graphics family

            if(indices->isComplete())
                return;

            i++;
        }

        m_queueFamilys = indices;

        // Create queues
        float queuePriority = 1.0f;

        vk::DeviceQueueCreateInfo queueCreateInfo(
            {},
            m_queueFamilys->graphicsFamily.first,
            1,
            &queuePriority
        );

        vk::PhysicalDeviceFeatures deviceFeatures;

        
    }
}

/** Default Destructor */
Vulkan_RenderDevice::~Vulkan_RenderDevice()
{
    if(m_enableValidationLayers)
        m_vkInstance.destroyDebugUtilsMessengerEXT(m_vkDebugMessenger, nullptr, m_vkDispatchLoader);

    m_vkInstance.destroy();

}

VkBool32 
Vulkan_RenderDevice::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
    void*                                            pUserData)
{
    if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        Log::LogMessage("Vulkan Render Device", pCallbackData->pMessage);

    if((messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) || (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT))
        Log::LogError("Vulkan Render Device", pCallbackData->pMessage);

    return VK_FALSE;
}