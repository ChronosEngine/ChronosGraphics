add_executable(APITesting main.cpp)

target_include_directories(APITesting PUBLIC "${PROJECT_SOURCE_DIR}/Source")

target_link_libraries(APITesting ChronosGraphics)