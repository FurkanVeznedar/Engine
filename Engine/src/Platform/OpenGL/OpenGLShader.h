#ifndef _OPENGLSHADER_H_
#define _OPENGLSHADER_H_

#include <glm/glm.hpp>

#include "Engine/Renderer/Shader.h"

namespace Engine {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexpath, const std::string& fragmentpath);
        virtual ~OpenGLShader();

        virtual void Use() const override;
        virtual void Unuse() const override;

        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetVec2(const std::string &name, const glm::vec2 &value) const;
        void SetVec2(const std::string &name, float x, float y) const;
        void SetVec3(const std::string &name, const glm::vec3 &value) const;
        void SetVec3(const std::string &name, float x, float y, float z) const;
        void SetVec4(const std::string &name, const glm::vec4 &value) const;
        void SetVec4(const std::string &name, float x, float y, float z, float w) const;
        void SetMat2(const std::string &name, const glm::mat2 &mat) const;
        void SetMat3(const std::string &name, const glm::mat3 &mat) const;
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;

        unsigned int GetUniformLoc(const std::string& name) const;

        inline const uint32_t GetID() const { return m_RendererID; }
    private:
        uint32_t m_RendererID;
    };
}

#endif // _OPENGLSHADER_H_