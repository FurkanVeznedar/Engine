#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Engine {

    class Renderer
    {
    public:
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void SubmitGeometry(const Ref<Shader>& shader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 VPMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };

}

#endif // _RENDERER_H_