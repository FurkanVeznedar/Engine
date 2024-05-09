#ifndef _SHADER_H_
#define _SHADER_H_

namespace Engine {

    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Use() const = 0;
        virtual void Unuse() const = 0;

        static Shader* Create(const std::string& vertexpath, const std::string& fragmentpath);
    };
}

#endif // _SHADER_H_