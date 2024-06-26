#include "Enpch.h"
#include "Renderer2D.h"

#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float texindex;
        float TilingFactor;
    };

    struct Renderer2DData
    {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32; // TODO: Rendercaps

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 = white texture

        glm::vec4 QuadVertexPositions[4];

        Renderer2D::Statistics Stats;
    };

    static Renderer2DData s_Data;

    Renderer2D::Renderer2D()
    {
    }

    void Renderer2D::Init()
    {
        EN_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout({
            { Engine::ShaderDataType::Float3, "a_Position" },
            { Engine::ShaderDataType::Float4, "a_Color" },
            { Engine::ShaderDataType::Float2, "a_TexCoord" },
            { Engine::ShaderDataType::Float, "a_TexIndex" },
            { Engine::ShaderDataType::Float, "a_TilingFactor" }
        });
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        uint32_t* QuadIndices = new uint32_t[s_Data.MaxIndices];

        uint32_t offset = 0;
        for(uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
        {
            QuadIndices[i + 0] = offset + 0;
            QuadIndices[i + 1] = offset + 1;
            QuadIndices[i + 2] = offset + 2;

            QuadIndices[i + 3] = offset + 2;
            QuadIndices[i + 4] = offset + 3;
            QuadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> QuadIB = IndexBuffer::Create(QuadIndices, s_Data.MaxIndices);
        s_Data.QuadVertexArray->SetIndexBuffer(QuadIB);
        delete[] QuadIndices;

        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whitetexturedata = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whitetexturedata, sizeof(uint32_t));

        int samplers[s_Data.MaxTextureSlots];
        for(int i = 0; i < s_Data.MaxTextureSlots; i++) samplers[i] = i;

        s_Data.TextureShader = Shader::Create("TextureShader", Engine::Log::GetShadersDir() + "TextureVertex.txt", Engine::Log::GetShadersDir() + "TextureFragment.txt");
        s_Data.TextureShader->Use();
        s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        s_Data.QuadVertexPositions[0] = {-0.5, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[1] = { 0.5, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[2] = { 0.5,  0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[3] = {-0.5,  0.5f, 0.0f, 1.0f};
    }

    void Renderer2D::ShutDown()
    {
        EN_PROFILE_FUNCTION();
    }
    
    void Renderer2D::BeginScene(const Camera& camera)
    {
        EN_PROFILE_FUNCTION();

        s_Data.TextureShader->Use();
        s_Data.TextureShader->SetMat4("u_VPMatrix", camera.GetVPMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }
    
    void Renderer2D::EndScene()
    {
        EN_PROFILE_FUNCTION();

        uint32_t DataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, DataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++) s_Data.TextureSlots[i]->Bind(i);
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

        s_Data.Stats.NumDrawC++;
    }

    void Renderer2D::FlushandReset()
    {
        EndScene();

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        EN_PROFILE_FUNCTION();

        if(s_Data.QuadIndexCount >= s_Data.MaxIndices) FlushandReset();

        const float textureindex = 0.0f; // White Texture
        const float tilingfactor = 1.0f;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingfactor, tintcolor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        EN_PROFILE_FUNCTION();

        if(s_Data.QuadIndexCount >= s_Data.MaxIndices) FlushandReset();

        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureindex = 0.0f;
        for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureindex = (float)i;
                break;
            }
        }

        if(textureindex == 0.0f)
        {
            textureindex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        EN_PROFILE_FUNCTION();

        if(s_Data.QuadIndexCount >= s_Data.MaxIndices) FlushandReset();

        const float textureindex = 0.0f; // White Texture
        const float tilingfactor = 1.0f;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingfactor, tintcolor);
    }
    
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingfactor, const glm::vec4& tintcolor)
    {
        EN_PROFILE_FUNCTION();

        if(s_Data.QuadIndexCount >= s_Data.MaxIndices) FlushandReset();

        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureindex = 0.0f;
        for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureindex = (float)i;
                break;
            }
        }

        if(textureindex == 0.0f)
        {
            textureindex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->texindex = textureindex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingfactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::ResetStats()
    {
        memset(&s_Data.Stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Data.Stats;
    }
}