#ifndef __CHRONOS_GRAPHICS_SHADER_HPP__
#define __CHRONOS_GRAPHICS_SHADER_HPP__

#include <vector>

/** Determines what the shaders job is */
struct ShaderType
{
    enum Enum
    {
        Vertex,
        Fragment
    };
};

/** Shaders change how this images displayed to the screen look */
class Shader
{

public:
    /** Default Constructor */
    Shader();

    /** Internal Constructor */
    Shader(
        std::vector<char> shaderCode, 
        ShaderType::Enum shaderType);

public:
    /** Default Destructor */
    virtual ~Shader();

};

#endif // __CHRONOS_GRAPHICS_SHADER_HPP__