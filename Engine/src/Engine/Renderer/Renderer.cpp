#include "Enpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine {

    glm::mat4 Renderer::VPMatrix = glm::mat4(1.0f);

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(const Ref<Camera>& camera)
    {
        // takes all the scene parameters;
        // make sure shaders get correct uniforms which enviroment maps, camre and etc.
        camera->UpdateCamera();
        VPMatrix = camera->GetVPMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::SubmitGeometry(const Ref<Shader>& shader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform)
    {
        shader->Use();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("VPMatrix", VPMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("Transform", transform);

        vertexarray->Bind();
        RenderCommand::DrawIndexed(vertexarray);
    }
}