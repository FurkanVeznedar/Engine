#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Engine {

    class Renderer
    {
    public:
        static void Init();

        static void BeginScene(const Ref<Camera>& camera);
        static void EndScene();

        static void SubmitGeometry(const Ref<Shader>& shader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static glm::mat4 VPMatrix;
    };

}

#endif // _RENDERER_H_