#include "Enpch.h"
#include "Renderer2D.h"

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    };  

    static Renderer2DStorage* s_Data;

    Renderer2D::Renderer2D()
    {
    }

    void Renderer2D::Init()
    {
        EN_PROFILE_FUNCTION();

        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();

        float squarevertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.2f, 0.3f, 0.8f, 1.0f
        };

        Ref<VertexBuffer> SquareVB;
        SquareVB.reset(VertexBuffer::Create(squarevertices, sizeof(squarevertices)));
        SquareVB->SetLayout({
            { Engine::ShaderDataType::Float3, "a_Position" },
            { Engine::ShaderDataType::Float2, "a_TextCoord" },
            { Engine::ShaderDataType::Float4, "a_Color" }
        });
        s_Data->QuadVertexArray->AddVertexBuffer(SquareVB);

        uint32_t squareindices[] = {
            0, 1, 2, 2, 3 ,0
        };
        Ref<IndexBuffer> SquareIB;
        SquareIB.reset(IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
        s_Data->QuadVertexArray->SetIndexBuffer(SquareIB);

        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whitetexturedata = 0xffffffff;
        s_Data->WhiteTexture->SetData(&whitetexturedata, sizeof(uint32_t));

        s_Data->TextureShader = Shader::Create("TextureShader", Engine::Log::GetShadersDir() + "TextureVertex.txt", Engine::Log::GetShadersDir() + "TextureFragment.txt");
        s_Data->TextureShader->Use();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::ShutDown()
    {
        EN_PROFILE_FUNCTION();

        delete s_Data;
    }
    
    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        EN_PROFILE_FUNCTION();

        s_Data->TextureShader->Use();
        s_Data->TextureShader->SetMat4("u_VPMatrix", camera.GetVPMatrix());
    }
    
    void Renderer2D::EndScene()
    {
        EN_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        EN_PROFILE_FUNCTION();

        s_Data->TextureShader->SetVec4("u_Color", color);
        s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);
        s_Data->WhiteTexture->Bind();

        // For rotation translate * rotation * scale
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingfactor, tintcolor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        EN_PROFILE_FUNCTION();

        s_Data->TextureShader->SetVec4("u_Color", tintcolor);
        s_Data->TextureShader->SetFloat("u_TilingFactor", tilingfactor);
        texture->Bind();

        // For rotation translate * rotation * scale
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        EN_PROFILE_FUNCTION();

        s_Data->TextureShader->SetVec4("u_Color", color);
        s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);
        s_Data->WhiteTexture->Bind();

        // For rotation translate * rotation * scale
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingfactor, tintcolor);
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        EN_PROFILE_FUNCTION();

        s_Data->TextureShader->SetVec4("u_Color", tintcolor);
        s_Data->TextureShader->SetFloat("u_TilingFactor", tilingfactor);
        texture->Bind();

        // For rotation translate * rotation * scale
        glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}