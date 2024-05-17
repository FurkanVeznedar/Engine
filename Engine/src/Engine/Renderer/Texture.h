#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include "Engine/Core/Base.h"

namespace Engine {

    class Texture
    {
    public:
        ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        ~Texture2D() = default;
        
        static Ref<Texture2D> Create(const std::string& path);
    };
}

#endif // _TEXTURE_H
