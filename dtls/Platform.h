#pragma once

// Define platform macros
#ifdef __linux__
#define PLATFORM_LINUX
#elif defined _WIN32
#define PLATFORM_WINDOWS
#else
#define PLATFORM_UNKNOWN
#endif


// Define LIBRARY_API to export/import functions
#ifdef PLATFORM_LINUX

#define EXPORT __attribute__((visibility("default")))
#define IMPORT __attribute__((visibility("hidden")))

#elif defined PLATFORM_WINDOWS

#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)

#else 

#define EXPORT
#define IMPORT

#endif 

#ifdef LIBRARY_EXPORT

#define LIBRARY_API EXPORT

#else

#define LIBRARY_API IMPORT

#endif