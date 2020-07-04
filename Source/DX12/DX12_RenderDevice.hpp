#ifndef __CHRONOS_GRAPHICS_DX12_RENDERDEVICE_HPP__
#define __CHRONOS_GRAPHICS_DX12_RENDERDEVICE_HPP__

#include "../RenderDevice.hpp"

// DirectX 12 Headers
#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// Some windows thing, Runtime
#include <wrl.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "../Window.hpp"

using namespace DirectX;
using namespace Microsoft::WRL;

class DX12_RenderDevice
    : public RenderDevice
{

public:
    /** Default Constructor */
    DX12_RenderDevice();

    /** Internal Constructor */
    DX12_RenderDevice(
        const char* windowName);

public:
    /** Default Destructor */
    ~DX12_RenderDevice();

public:
    /** Create a DX12 pipeline object */
    Pipeline*
    CreatePipeline(
        const std::string pipelinePath);

private:
    static const UINT FrameCount = 2;

    D3D12_VIEWPORT m_viewport;
    D3D12_RECT scissorRect;
    ComPtr<ID3D12Device> dxDevice;
    ComPtr<ID3D12CommandQueue> dxCommandQueue;
    ComPtr<IDXGISwapChain3> dxgiSwapChain;
    ComPtr<ID3D12DescriptorHeap> dxRtvHeap;
    ComPtr<ID3D12Resource> dxRenderTargets[FrameCount];
    UINT rtvDescriptorSize;
    ComPtr<ID3D12CommandAllocator> dxCommandAllocator;

    // Syncronization Objects
    UINT frameIndex; 

};

#endif // __CHRONOS_GRAPHICS_DX12_RENDERDEVICE_HPP__