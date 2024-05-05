#ifndef _CORE_H_
#define _CORE_H_

#include <iostream>

#ifdef EN_ENABLE_ASSERTS
    #define EN_ASSERT(x, ...) { if(!(x)) { EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define EN_ENGINE_ASSERT(x, ...) { if(!(x)) { EN_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define EN_ASSERT(x, ...)
    #define EN_ENGINE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define EN_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define GetShadersDirs "C:/Users/furka/Desktop/Furkan VEZNEDAR/03-Programming/11-FEAEngine/Engine/Assets/Shaders/"

#endif // _CORE_H_