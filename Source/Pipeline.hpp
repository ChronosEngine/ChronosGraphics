#ifndef __CHRONOS_GRAPHICS_PIPELINE_HPP__
#define __CHRONOS_GRAPHICS_PIPELINE_HPP__

class RenderDevice;
class Shader;

#include <string>

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
    virtual void LoadPipelineFromFile();

public:
    /** Default Destructor */
    virtual ~Pipeline();

};

// Default.pipeline (Pseudofile)

/*
{
	"Name": "Default Pipeline",
	"Elements": [
		{
			"POSITION": "Vec3"
		},
		{
			"COLOR": "Vec3"
		}
	],
	"Files": [
		{
            "Vertex" : "defaultVertex.hlsl"
        },
		{
            "Fragment" : "defaultFragment.hlsl"
        }
	]
}
*/

#endif // __CHRONOS_GRAPHICS_PIPELINE_HPP__