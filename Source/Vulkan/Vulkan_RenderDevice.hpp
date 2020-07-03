#ifndef __CHRONOS_GRAPHICS_VULKAN_RENDERDEVICE_HPP__
#define __CHRONOS_GRAPHICS_VULKAN_RENDERDEVICE_HPP__

#include "../RenderDevice.hpp"

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


};

#endif // __CHRONOS_GRAPHICS_VULKAN_RENDERDEVICE_HPP__