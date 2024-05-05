#ifndef _OPENGLRENDERERAPI_H_
#define _OPENGLRENDERERAPI_H_

#include "Engine/Renderer/RendererAPI.h"

namespace Engine {

    class OpenGLRendererAPI : public RendererAPI
    {
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexarray) override;
    };
}

#endif // _OPENGLRENDERERAPI_H_