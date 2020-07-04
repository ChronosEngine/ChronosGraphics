#include "Graphics.hpp"

int main()
{

    RenderDevice* renderDevice = CreateRenderDevice(RenderType::DX12, "API Testing");

    Pipeline* testingPipeline = renderDevice->CreatePipeline("C:\\Users\\Steak\\Documents\\ChronosGraphics\\Resources\\Pipelines\\Testing\\Testing.pipeline");

    while(!renderDevice->getWindow()->shouldWindowClose())
    {
        glfwPollEvents();
    }

    delete renderDevice;
}