#include "DX12_RenderDevice.hpp"

#include <vector>

#include "DX12_Pipeline.hpp"
#include "../Log.hpp"

void GetBestHardwareAdapter(IDXGIFactory7* pFactory, IDXGIAdapter1** ppAdapter);

/** Default Constructor */
DX12_RenderDevice::DX12_RenderDevice()
{

}

/** Internal Constructor */
DX12_RenderDevice::DX12_RenderDevice(
    const char* windowName)
{
    ///////////Initalize GLFW//////////
    glfwInit();

    renderWindow = new Window(windowName, false, [](){ glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); });

    ///////////Initalize DX12//////////

    // Enable the D3D12 debug layer
#ifdef _DEBUG
    {
        ComPtr<ID3D12Debug> debugController;
        if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
        }
    }
#endif

    ComPtr<IDXGIFactory7> factory;
    if(!SUCCEEDED(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory))))
    {
        Log::LogError("DX12 Render Device", "Could not create DXGI factory!");
    }

    bool warpDevice = false; // TODO: Check the command line args for this
    // Check if user wants a warp device
    if(warpDevice)
    {
        // Get the adapter device
        ComPtr<IDXGIAdapter> warpAdapter;
        if(!SUCCEEDED(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter))))
        {
            Log::LogError("DX12 Render Device", "Could not create the warp adapter!");
        }

        // Create the DX12 Device
        if(!SUCCEEDED(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&dxDevice))))
        {
            Log::LogError("DX12 Render Device", "Could not create the DX12 device!");
        }
    }
    else
    {
        ComPtr<IDXGIAdapter1> hardwareAdapter;
        GetBestHardwareAdapter(factory.Get(), &hardwareAdapter);

        if(!SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&dxDevice))))
        {
            Log::LogError("DX12 Render Device", "Could not create the DX12 device!");
        }
    }

    //////////Initalize the Command Queue//////////
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    if(!SUCCEEDED(dxDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&dxCommandQueue))))
    {
        Log::LogError("DX12 Render Device", "Could not create the command queue!");
    }

    //////////Create the Swap Chain//////////
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = FrameCount;
    swapChainDesc.BufferDesc.Width = 100;
    swapChainDesc.BufferDesc.Height = 100;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.OutputWindow = glfwGetWin32Window(renderWindow->windowHandle);
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = true;

    ComPtr<IDXGISwapChain> swapChain;
    if(!SUCCEEDED(factory->CreateSwapChain(dxCommandQueue.Get(), &swapChainDesc, &swapChain)))
    {
        Log::LogError("DX12 Render Device", "Could not create the swap chain!");
    }

    if(!SUCCEEDED(swapChain.As(&dxgiSwapChain)))
    {
        Log::LogError("DX12 Render Device", "Could not set the swap chain!");
    }

    if(!SUCCEEDED(factory->MakeWindowAssociation(glfwGetWin32Window(renderWindow->windowHandle), DXGI_MWA_NO_ALT_ENTER)))
    {
        Log::LogError("DX12 Render Device", "Could not make window association!");
    }
    
    frameIndex = dxgiSwapChain->GetCurrentBackBufferIndex();
    

    //////////Create Descriptor Heaps//////////
    {
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = FrameCount;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    
        if(!SUCCEEDED(dxDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&dxRtvHeap))))
        {
            Log::LogError("DX12 Render Device", "Could not create descriptor heap!");
        }

        rtvDescriptorSize = dxDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }


    //////////Create Frame Resources//////////
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(dxRtvHeap->GetCPUDescriptorHandleForHeapStart());

        // Create an RTV for every frame
        for(UINT n = 0; n < FrameCount; n++)
        {
            if(!SUCCEEDED(swapChain->GetBuffer(n, IID_PPV_ARGS(&dxRenderTargets[n]))))
            {
                Log::LogError("DX12 Render Device", "Could not create a render target!");
            }

            dxDevice->CreateRenderTargetView(dxRenderTargets[n].Get(), nullptr, rtvHandle);
            rtvHandle.Offset(1, rtvDescriptorSize);
        }
    }

    if(!SUCCEEDED(dxDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&dxCommandAllocator))))
    {
        Log::LogError("DX12 Render Device", "Could not create the command allocator!");
    }


}

DX12_RenderDevice::~DX12_RenderDevice()
{
    
}

Pipeline*
DX12_RenderDevice::CreatePipeline(
    const std::string pipelinePath)
{
    return new DX12_Pipeline(this, pipelinePath);
}

////////// Helper Functions //////////
void GetBestHardwareAdapter(IDXGIFactory7* pFactory, IDXGIAdapter1** ppAdapter)
{
    *ppAdapter = nullptr;

    // We select the largest memory adapter as the better one
    // TODO: Make it so that the Game dev can select the graphics card
    IDXGIAdapter4* pLargestMemoryAdapter = nullptr;

    for(UINT adapterIndex = 0; ; ++adapterIndex)
    {
        IDXGIAdapter4* pAdapter = nullptr;
        if(!SUCCEEDED(pFactory->EnumAdapterByGpuPreference(adapterIndex, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&pAdapter))))
        {
            // No more adapters to enumerate
            break;
        }

        // Check if the adapter supports D3D12
        if(!SUCCEEDED(D3D12CreateDevice(static_cast<IDXGIAdapter1*>(pAdapter), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
        {
            pAdapter->Release(); // If the adapter failed release it we will not be using it
        }
        else // Adapter did not fail the check so keep going
        {
            // Check to see which adapter is the better one

            DXGI_QUERY_VIDEO_MEMORY_INFO memoryInfo = {};
            pAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memoryInfo);


            // If there is no largest this first one must be
            if(pLargestMemoryAdapter == nullptr)
            {
                pLargestMemoryAdapter = pAdapter;
            }
            else
            {
                DXGI_QUERY_VIDEO_MEMORY_INFO largestMemoryInfo = {};
                pLargestMemoryAdapter->QueryVideoMemoryInfo(adapterIndex, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memoryInfo);

                if(largestMemoryInfo.Budget < memoryInfo.Budget)
                {
                    pLargestMemoryAdapter = pAdapter;
                }
            }
        }
    }

    *ppAdapter = static_cast<IDXGIAdapter1*>(pLargestMemoryAdapter);
}