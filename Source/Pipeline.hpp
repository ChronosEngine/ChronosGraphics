#ifndef __CHRONOS_GRAPHICS_PIPELINE_HPP__
#define __CHRONOS_GRAPHICS_PIPELINE_HPP__

class RenderDevice;
class Shader;

#include <string>
#include <vector>

/** Shaders that group together */
class Pipeline
{

public:
    /** Default Constructor */
    Pipeline();

    /** Internal Constructor */
    Pipeline(
        RenderDevice* renderDev,
        const std::string pipelinePath);

public:
    /** Default Destructor */
    virtual ~Pipeline();

public:
    std::vector<std::pair<std::string, std::string>> Elements;

};

#endif // __CHRONOS_GRAPHICS_PIPELINE_HPP__