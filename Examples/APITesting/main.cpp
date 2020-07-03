#include "Graphics.hpp"

int main()
{

    RenderDevice* renderDevice = CreateRenderDevice(RenderType::DX12, "API Testing");

    while(!renderDevice->getWindow()->shouldWindowClose())
    {
        glfwPollEvents();
    }

    delete renderDevice;
}