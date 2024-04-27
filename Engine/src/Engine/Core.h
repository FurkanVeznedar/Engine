#ifndef _CORE_H_
#define _CORE_H_

#include <iostream>

#ifdef EN_PLATFORM_WINDOWS
#if EN_DYNAMIC_LINK
    #ifdef EN_BUILD_DLL
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#else
    #define ENGINE_API
#endif
#else
    #error Engine only supports windows!
#endif

#ifdef EN_DEBUG
    #define EN_ENABLE_ASSERTS
#endif

#ifdef EN_ENABLE_ASSERTS
    #define EN_ASSERT(x, ...) { if(!(x)) { EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define EN_ENGINE_ASSERT(x, ...) { if(!(x)) { EN_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define EN_ASSERT(x, ...)
    #define EN_ENGINE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define EN_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#endif // _CORE_H_