#ifndef __CHRONOS_GRAPHICS_VULKAN_RENDERDEVICE_HPP__
#define __CHRONOS_GRAPHICS_VULKAN_RENDERDEVICE_HPP__

#include "../RenderDevice.hpp"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>


struct QueueFamilyIndices;

/** Vulkan API abstraction of the render device */
class Vulkan_RenderDevice
    : public RenderDevice
{

public:
    /** Default Constructor */
    Vulkan_RenderDevice();

    /** Internal Constructor */
    Vulkan_RenderDevice(
        const char* windowName);

public:
    /** Default Destructor */
    ~Vulkan_RenderDevice();

public:

    /** Debug callback that vulkan will use when displaying errors */
    static
    VkBool32 debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
        const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
        void*                                            pUserData);

public:
    /** Vulkan instance */
    vk::Instance m_vkInstance;
    
    /** Dynamic loader allows the vulkan-hpp api know what functions to load */
    vk::DispatchLoaderDynamic m_vkDispatchLoader;

    /** Debug messenger */
    vk::DebugUtilsMessengerEXT m_vkDebugMessenger;

    /** The physical gpu */
    vk::PhysicalDevice m_vkPhysicalDevice;

    /** The logical device that many objects are managed from */
    vk::Device m_vkDevice;

    /** The graphics queues that tell the gpu what to do */
    QueueFamilyIndices* m_queueFamilys;

    /** If there is debug messages that vulkan can log */
    bool m_validationLayersSupported;

    /** validation layers tell vulkan what to log */
    const std::vector<const char*> m_validationLayers =
    {
        "VK_LAYER_KHRONOS_validation"
    };

    /** Only enable logging when were debugging */
#ifdef NDEBUG
    const bool m_enableValidationLayers = false;
#else
    const bool m_enableValidationLayers = true;
#endif

};

/** A place where all the queues can be found */
struct QueueFamilyIndices
{
    // uin32_t is the graphics family
    // bool is if the graphics family exists
    // This is a version of std::optional for any version of c++11 and higher 
    std::pair<uint32_t, bool> graphicsFamily;

    /** Tells us if all the queues are filled */
    bool isComplete()
    {
        return graphicsFamily.second;
    }
};



#endif // __CHRONOS_GRAPHICS_VULKAN_RENDERDEVICE_HPP__