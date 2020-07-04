#include "RenderDevice.hpp"

#include "Platform.hpp"
#include "Window.hpp"
#include "Pipeline.hpp"


#ifdef _WIN32
    #include "DX12/DX12_RenderDevice.hpp"
#endif

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

Pipeline*
RenderDevice::CreatePipeline(
    std::string pipelinePath)
{
    return new Pipeline(this, pipelinePath); // If there is no render device just give the base pipeline with no code
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
        
#ifdef _WIN32
        case RenderType::DX12:
            return new DX12_RenderDevice(windowName);
        break;
#endif
        case RenderType::GLES:
            return new GLES_RenderDevice(windowName);
        break;

        // Get the recommended api for the platform
        case RenderType::Recommended:
            switch(currentPlatform)
            {

#ifdef _WIN32
                case ChronosPlatform::Windows:
                    return new DX12_RenderDevice(windowName);
                break;
#endif
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