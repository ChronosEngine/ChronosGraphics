cmake_minimum_required(VERSION 3.10)

project(ChronosGraphics)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Build Third Party librarys
add_subdirectory(ThirdParty)

set(CHRONOS_GRAPHICS_HAS_GLES ON)
set(CHRONOS_GRAPHICS_HAS_VULKAN ON)

# Build Chronos Graphics
add_subdirectory(Source)

# Build Examples
add_subdirectory(Examples)

