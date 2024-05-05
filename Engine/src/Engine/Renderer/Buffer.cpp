#include "Enpch.h"
#include "Buffer.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: EN_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        EN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: EN_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }

        EN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}