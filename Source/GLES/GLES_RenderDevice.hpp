#ifndef __CHRONOS_GRAPHICS_GLES_RENDERDEVICE_HPP__
#define __CHRONOS_GRAPHICS_GLES_RENDERDEVICE_HPP__

#include "../RenderDevice.hpp"

class GLES_RenderDevice
    : public RenderDevice
{

public:
    /** Default Constructor */
    GLES_RenderDevice();

    /** Internal Constructor */
    GLES_RenderDevice(
        const char* windowName);

public:
    /** Default Destructor */
    ~GLES_RenderDevice();

public:
    

public:



};

#endif // __CHRONOS_GRAPHICS_GLES_RENDERDEVICE_HPP__