#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Engine {

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Use() const = 0;
        virtual void Unuse() const = 0;

        virtual void SetInt(const std::string& name, const int& value) = 0;
        virtual void SetIntArray(const std::string& name, const int* values, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, const float& value) = 0;
        virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& name, const std::string& vertexpath, const std::string& fragmentpath);
    };

    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        // Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& vertexpath, const std::string& fragmentpath);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}

#endif // _SHADER_H_