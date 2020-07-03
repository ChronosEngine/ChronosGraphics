#ifndef __CHRONOS_GRAPHICS_WINDOW_HPP__
#define __CHRONOS_GRAPHICS_WINDOW_HPP__

#include <glfw/glfw3.h>

/** A window abstraction from glfw3 */
class Window
{

public:
    /** Default Constructor */
    Window(
        const char* windowName,
        const bool fullscreen,
        void (*windowSettingsFunc)());

public:
    /** Default Destructor */
    ~Window();

public:
    /** Check if window will close */
    bool 
    shouldWindowClose();

    /** Set the window size */
    void 
    setWindowSize(
        const int sizeX, 
        const int sizeY);

    /** Get the frame buffer size */
    void 
    getFramebufferSize(
        int* sizeX, 
        int* sizeY);

    /** Get the windows context scale */
    void 
    getContentScale(
        float* sizeX, 
        float* sizeY);

    /** Sets how large a window can be */
    void 
    setSizeLimits(
        const int minWidth, 
        const int minHeight, 
        const int maxWidth, 
        const int maxHeight);

    /** Set the window position on screen */
    void 
    setPosition(
        const int posX, 
        const int posY);

    /** Change the title of the window */
    void 
    setTitle(
        const char* title);

    /** Change the window opacity */
    void 
    setWindowOpacity(
        const float opacity);

    /** Get the current window opacity */
    float 
    getWindowOpacity();

public:
    GLFWwindow* windowHandle;

};

#endif // __CHRONOS_GRAPHICS_WINDOW_HPP__