set(Sources
    "Log.cpp"

    "Window.cpp"
    "RenderDevice.cpp"
    "Pipeline.cpp"
)


if(CHRONOS_GRAPHICS_HAS_DX12)
    list(APPEND Sources
        "DX12/DX12_RenderDevice.cpp"
        "DX12/DX12_Pipeline.cpp"
    )
endif()

if(CHRONOS_GRAPHICS_HAS_GLES)
    list(APPEND Sources
        "GLES/GLES_RenderDevice.cpp"    
    )
endif()

if(CHRONOS_GRAPHICS_HAS_VULKAN)
    list(APPEND Sources 
        "Vulkan/Vulkan_RenderDevice.cpp"
    )
endif()



add_library(ChronosGraphics STATIC ${Sources})

# Link Third Party Libraries
target_link_libraries(ChronosGraphics glfw)

if(WIN32)
    find_package(D3D12 REQUIRED)

    if(D3D12_FOUND)
        message("D3D12 Found!")
        
        target_include_directories(ChronosGraphics PUBLIC ${D3D12_INCLUDE_DIRS})
        target_link_libraries(ChronosGraphics ${D3D12_LIBRARIES})
    endif()
endif()