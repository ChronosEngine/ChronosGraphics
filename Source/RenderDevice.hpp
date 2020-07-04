#ifndef __CHRONOS_GRAPHICS_RENDERDEVICE_HPP__
#define __CHRONOS_GRAPHICS_RENDERDEVICE_HPP__

#include <string>

class Window;
class Pipeline;

struct RenderType
{
    enum Enum
    {
        NoRender,   // Does not draw to the screen or create a window
        Vulkan,
        DX12,
        GLES,
        Recommended // Chooses the best render API for the platform
    };
};

/** Render device is an abstraction to change the rendering API being used. */
class RenderDevice
{

public:
    /** Default Constructor */
    RenderDevice();

    /** Internal Constructor */
    RenderDevice(
        const char* windowName);

public:
    /** Default Destructor */
    virtual 
    ~RenderDevice();

public:
    /** Creates a pipeline object */
    virtual 
    Pipeline* 
    CreatePipeline(
        std::string pipelinePath);

public:
    virtual 
    Window* 
    getWindow();



protected:
    Window* renderWindow;

    friend class DX12_RenderDevice;

};

RenderDevice*
CreateRenderDevice(
    const RenderType::Enum renderType,
    const char* windowName);

#endif // __CHRONOS_GRAPHICS_RENDERDEVICE_HPP__