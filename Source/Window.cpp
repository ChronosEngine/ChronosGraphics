#include "Window.hpp"


/** Default Constructor */
Window::Window(
    const char* windowName,
    const bool fullscreen = true, 
    void (*windowSettingsFunc)() = nullptr)
{

    GLFWmonitor* priMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidMode = glfwGetVideoMode(priMonitor);

    int width = vidMode->width;
    int height = vidMode->height;

    if(!fullscreen)
    {
        priMonitor = nullptr;
    }
    
    windowSettingsFunc();

    windowHandle = glfwCreateWindow(width, height, windowName, priMonitor, nullptr);
}

/** Default Destructor */
Window::~Window()
{
    glfwDestroyWindow(windowHandle);
}


/** Check if window will close */
bool 
Window::shouldWindowClose()
{
    return glfwWindowShouldClose(windowHandle);
}

/** Set the window size */
void 
Window::setWindowSize(
    const int sizeX, 
    const int sizeY)
{
    glfwSetWindowSize(windowHandle, sizeX, sizeY);
}

/** Get the frame buffer size */
void 
Window::getFramebufferSize(
    int* sizeX, 
    int* sizeY)
{
    glfwGetFramebufferSize(windowHandle, sizeX, sizeY);
}

/** Get the windows context scale */
void 
Window::getContentScale(
    float* sizeX, 
    float* sizeY)
{
    glfwGetWindowContentScale(windowHandle, sizeX, sizeY);
}

/** Sets how large a window can be */
void 
Window::setSizeLimits(
    const int minWidth, 
    const int minHeight, 
    const int maxWidth, 
    const int maxHeight)
{
    glfwSetWindowSizeLimits(windowHandle, minWidth, minHeight, maxWidth, maxHeight);
}

/** Set the window position on screen */
void 
Window::setPosition(
    const int posX, 
    const int posY)
{
    glfwSetWindowPos(windowHandle, posX, posY);
}

/** Change the title of the window */
void 
Window::setTitle(
    const char* title)
{
    glfwSetWindowTitle(windowHandle, title);
}

/** Change the window opacity */
void 
Window::setWindowOpacity(
    const float opacity)
{
    glfwSetWindowOpacity(windowHandle, opacity);
}

/** Get the current window opacity */
float 
Window::getWindowOpacity()
{
    return glfwGetWindowOpacity(windowHandle);
}