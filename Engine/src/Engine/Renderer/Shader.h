#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

namespace Engine {

    class Shader
    {
    public:
        Shader(const std::string& VertexSrc, const std::string& FragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RendererID;
    };
}

#endif // _SHADER_H_