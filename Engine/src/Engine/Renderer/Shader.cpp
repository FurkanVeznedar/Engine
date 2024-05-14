#include "Enpch.h"
#include "Shader.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine {

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexpath, const std::string& fragmentpath) 
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: EN_ENGINE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexpath, fragmentpath);
        }

        EN_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        EN_ENGINE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    // Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
    // {

    // }
    
    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexpath, const std::string& fragmentpath)
    {
        auto shader = Shader::Create(name, vertexpath, fragmentpath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        EN_ENGINE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
    
}