#include "Enpch.h"
#include "VertexArray.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

    VertexArray* VertexArray::Create() 
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: EN_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }

        EN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}