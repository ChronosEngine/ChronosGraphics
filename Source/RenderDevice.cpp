#include "RenderDevice.hpp"
#include "Window.hpp"
#include "Platform.hpp"

#include "DX12/DX12_RenderDevice.hpp"
#include "GLES/GLES_RenderDevice.hpp"
#include "Vulkan/Vulkan_RenderDevice.hpp"


/** Default Constructor */
RenderDevice::RenderDevice() 
{

}

/** Internal Constructor */
RenderDevice::RenderDevice(
    const char* windowName) 
{

}

/** Default Destructor */
RenderDevice::~RenderDevice() 
{
    
}

Window* 
RenderDevice::getWindow()
{
    return renderWindow;
}

RenderDevice*
CreateRenderDevice(
    const RenderType::Enum renderType,
    const char* windowName)
{

    switch(renderType)
    {
        case RenderType::NoRender:
            return new RenderDevice(windowName);
        break;

        case RenderType::Vulkan:
            return new Vulkan_RenderDevice(windowName);
        break;

        case RenderType::DX12:
            return new DX12_RenderDevice(windowName);
        break;

        case RenderType::GLES:
            return new GLES_RenderDevice(windowName);
        break;

        // Get the recommended api for the platform
        case RenderType::Recommended:
            switch(currentPlatform)
            {
                case ChronosPlatform::Windows:
                    return new DX12_RenderDevice(windowName);
                break;

                case ChronosPlatform::MacOS:
                    return new GLES_RenderDevice(windowName);
                break;

                case ChronosPlatform::Linux:
                    return new Vulkan_RenderDevice(windowName);
                break;

                default:
                    return new GLES_RenderDevice(windowName);
                break;

            };
        break;

        default:
            return new RenderDevice(windowName);
        break;


    };

}