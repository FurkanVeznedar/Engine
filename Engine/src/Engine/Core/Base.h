#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
    /* Window x64/x86 */
    #ifdef _WIN64
        /* Window x64*/
        #define EN_PLATFORM_WINDOWS
    #else
        /* Window x86*/
        #error "x86 Builds are not supported!"
    #endif
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

namespace Engine {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#endif // _BASE_H_