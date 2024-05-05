#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Engine {

    class Renderer
    {
    public:
        static void BeginScene(const std::shared_ptr<Camera>& camera);
        static void EndScene();

        static void SubmitGeometry(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexarray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static glm::mat4 MVPMatrix;
    };

}

#endif // _RENDERER_H_