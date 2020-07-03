#include "Log.hpp"

#include <iostream>

void Log::DebugLog(const std::string context, const std::string message)
{
#ifndef NDEBUG
    std::cout << "Debug | " << context << ": " << message << std::endl;
#endif 
}

void Log::LogMessage(const std::string context, const std::string message)
{
    std::cout << context << ": " << message << std::endl;
}

void Log::LogAssert(const bool assertation, const std::string context, const std::string message)
{

#ifndef NDEBUG // If this assertation fails douring release build may god help you.
    if(!assertation)
    {
        std::cout << "Assertation Failed | " << context << ": " << message << std::endl;
        
        // Pause the program
        std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
        std::cin.get();
    }
#endif

}

void Log::LogError(const std::string context, const std::string message)
{
    std::cout << "\033[0;31m" << context << ": " << message << "\033[0m" << std::endl;
}