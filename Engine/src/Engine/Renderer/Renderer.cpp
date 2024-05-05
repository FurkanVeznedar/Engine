#include "Enpch.h"
#include "Renderer.h"

namespace Engine {

    glm::mat4 Renderer::MVPMatrix = glm::mat4(1.0f);

    void Renderer::BeginScene(const std::shared_ptr<Camera>& camera)
    {
        // takes all the scene parameters;
        // make sure shaders get correct uniforms which enviroment maps, camre and etc.
        camera->UpdateCamera();
        MVPMatrix = camera->GetMVPMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::SubmitGeometry(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexarray)
    {
        shader->Use();
        shader->SetMat4("MVPMatrix", MVPMatrix);

        vertexarray->Bind();
        RenderCommand::DrawIndexed(vertexarray);
    }
}