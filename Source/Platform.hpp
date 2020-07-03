#ifndef __CHRONOS_GRAPHICS_PLATFORM_HPP__
#define __CHRONOS_GRAPHICS_PLATFORM_HPP__

    struct ChronosPlatform
    {
        enum Enum
        {
            Windows             = 0,
            MacOS               = 1,
            IPhoneSimulator     = 2,
            IPhone              = 3,
            Linux               = 4,
            Unix                = 5,
            Posix               = 6,
            Unknown             = -1
        };
    };



    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        // Windows
        static ChronosPlatform::Enum currentPlatform = ChronosPlatform::Windows;

    #elif __APPLE__
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            // IPhone simulator
            static ChronosPlatform::Enum currentPlatform = ChronosPlatform::IPhoneSimulator;

        #elif TARGET_OS_IPHONE
            // iOS device
            static ChronosPlatform::Enum currentPlatform = ChronosPlatform::IPhone;

        #elif TARGET_OS_MAC
            // Other kinds of Mac OS
            static ChronosPlatform::Enum currentPlatform = ChronosPlatform::MacOS;

        #else
            // Unknown apple platform
            static ChronosPlatform::Enum currentPlatform = ChronosPlatform::Unknown;

        #endif
    #elif __linux__
        // Linux
        static ChronosPlatform::Enum currentPlatform = ChronosPlatform::Linux;

    #elif __unix__ // all unices not caught above
        // Unix
        static ChronosPlatform::Enum currentPlatform = ChronosPlatform::Unix;

    #elif defined(_POSIX_VERSION)
        // POSIX
        static ChronosPlatform::Enum currentPlatform = ChronosPlatform::Posix;

    #else
        // Unknown platform
        static ChronosPlatform::Enum currentPlatform = ChronosPlatform::Unknown;

    #endif


#endif // __CHRONOS_GRAPHICS_PLATFORM_HPP__