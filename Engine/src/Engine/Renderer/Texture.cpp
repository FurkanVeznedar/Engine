#include "Enpch.h"
#include "Texture.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine {

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: EN_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }

        EN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}