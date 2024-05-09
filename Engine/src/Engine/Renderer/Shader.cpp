#include "Enpch.h"
#include "Shader.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine {

    Shader* Shader::Create(const std::string& vertexpath, const std::string& fragmentpath) 
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: EN_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexpath, fragmentpath);
        }

        EN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}