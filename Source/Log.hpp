#ifndef __CHRONOS_GRAPHICS_LOG_HPP__
#define __CHRONOS_GRAPHICS_LOG_HPP__

#include <string>

/** Log a message to the console */
class Log
{
public:
    
    /** Log a message but only if in debug mode */
    static 
    void 
    DebugLog(
        const std::string context,
        const std::string message);

    /** Log a message */
    static 
    void
    LogMessage(
        const std::string context, 
        const std::string message);
    
    /** Assertation with a log statement, does not work in release build */
    static 
    void 
    LogAssert(
        const bool assertation, 
        const std::string context, 
        const std::string message);

    /** Log a message that is discernable as an error from the console */
    static 
    void 
    LogError(
        const std::string context, 
        const std::string message);

};

#endif // __CHRONOS_GRAPHICS_LOG_HPP__