set(Sources
    "Log.cpp"

    "Window.cpp"
    "RenderDevice.cpp"
    "Pipeline.cpp"
)

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

# Include Vulkan
find_package(Vulkan REQUIRED)

if(Vulkan_FOUND)
    message("Vulkan Found!")

    target_include_directories(ChronosGraphics PUBLIC ${Vulkan_INCLUDE_DIR})
    target_link_libraries(ChronosGraphics ${Vulkan_LIBRARY})
endif()