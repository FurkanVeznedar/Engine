#include "Enpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Engine {

    Shader::Shader(const std::string& vertexpath, const std::string& fragmentpath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexpath);
            fShaderFile.open(fragmentpath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            EN_ENGINE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ, {0}", e.what());
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];
        
        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            EN_ENGINE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED, {0}", infoLog);
        };
        
        // similiar for Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            EN_ENGINE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED, {0}", infoLog);
        };
        
        // shader Program
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertex);
        glAttachShader(m_RendererID, fragment);
        glLinkProgram(m_RendererID);
        // print linking errors if any
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
            EN_ENGINE_ERROR("ERROR::SHADER::PROGRAM::COMPILATION_FAILED, {0}", infoLog);
        }
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Use() const
    {
        glUseProgram(m_RendererID);
    }
    
    void Shader::Unuse() const
    {
        glUseProgram(0);
    }

    void Shader::SetBool(const std::string &name, bool value) const
    {
        glUniform1i(GetUniformLoc(name), static_cast<int>(value));
    }

    void Shader::SetInt(const std::string &name, int value) const
    {
        glUniform1i(GetUniformLoc(name), value); 
    }
    
    void Shader::SetFloat(const std::string &name, float value) const
    {
        glUniform1f(GetUniformLoc(name), value); 
    }
    
    void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(GetUniformLoc(name), 1, &value[0]);
    }
    
    void Shader::SetVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(GetUniformLoc(name), x, y);
    }
    
    void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(GetUniformLoc(name), 1, &value[0]);
    }
    
    void Shader::SetVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(GetUniformLoc(name), x, y, z);
    }
    
    void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(GetUniformLoc(name), 1, &value[0]);
    }
    
    void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(GetUniformLoc(name), x, y, z, w);
    }
    
    void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(GetUniformLoc(name), 1, GL_FALSE, &mat[0][0]);
    }
    
    void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(GetUniformLoc(name), 1, GL_FALSE, &mat[0][0]);
    }
    
    void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &mat[0][0]);
    }

    unsigned int Shader::GetUniformLoc(const std::string& name) const
    {
        unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());

        if(location == -1)
        {
            EN_ENGINE_ERROR("Uniform Location Could NOT Find!");
            return 0;
        } else
        {
            return location;
        }
    }
    
}