#ifndef _OPENGLRENDERERAPI_H_
#define _OPENGLRENDERERAPI_H_

#include "Engine/Renderer/RendererAPI.h"

namespace Engine {

    class OpenGLRendererAPI : public RendererAPI
    {
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexarray) override;
    };
}

#endif // _OPENGLRENDERERAPI_H_