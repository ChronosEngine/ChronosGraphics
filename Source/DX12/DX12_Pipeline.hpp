#ifndef __CHRONOS_GRAPHICS_DX12_PIPELINE_HPP__
#define __CHRONOS_GRAPHICS_DX12_PIPELINE_HPP__

#include "../Pipeline.hpp"

// DirectX 12 Headers
#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// Some windows thing, Runtime
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

class DX12_RenderDevice;

class DX12_Pipeline
    : public Pipeline
{

public:
    /** Default Constructor */
    DX12_Pipeline();

    /** Internal Constructor */
    DX12_Pipeline(
        RenderDevice* renderDev,
        const std::string pipelinePath);

public:
    /** Default Destructor */
    ~DX12_Pipeline();

private:
    ComPtr<ID3DBlob> vertexShader;
    ComPtr<ID3DBlob> fragmentShader; // Pixel Shader

    DX12_RenderDevice* renderDevice;

};

#endif // __CHRONOS_GRAPHICS_DX12_PIPELINE_HPP__