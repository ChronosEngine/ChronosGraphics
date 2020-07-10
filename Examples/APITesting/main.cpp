#include "Graphics.hpp"

int main()
{

    RenderDevice* renderDevice = CreateRenderDevice(RenderType::Vulkan, "API Testing");

    Pipeline* testingPipeline = renderDevice->CreatePipeline("C:\\Users\\Caden\\Documents\\Projects\\ChronosGraphics\\Resources\\Pipelines\\Testing\\Testing.pipeline");

    //while(!renderDevice->getWindow()->shouldWindowClose())
    {
        //glfwPollEvents();
    }
    system("pause");

    delete renderDevice;
}