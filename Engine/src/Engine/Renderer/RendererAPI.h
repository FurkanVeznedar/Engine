#ifndef _RENDERERAPI_H_
#define _RENDERERAPI_H_

#include <glm/glm.hpp>

#include "Engine/Renderer/VertexArray.h"

namespace Engine {

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };
    public:
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexarray, uint32_t indexcount = 0) = 0;

        inline static API GetAPI() { return s_API; }
    private:
        static API s_API;

    };
}

#endif // _RENDERERAPI_H_