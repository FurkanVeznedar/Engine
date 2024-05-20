#include "Enpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Engine/Renderer/Renderer2D.h"

namespace Engine {

	Scope<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::Init()
    {
        EN_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        // takes all the scene parameters;
        // make sure shaders get correct uniforms which enviroment maps, camre and etc.
        s_SceneData->VPMatrix = camera.GetVPMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::SubmitGeometry(const Ref<Shader>& shader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform)
    {
        shader->Use();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadMat4("u_VPMatrix", s_SceneData->VPMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadMat4("u_Transform", transform);

        vertexarray->Bind();
        RenderCommand::DrawIndexed(vertexarray);
    }
}