#include "ShaderSpawner.hpp"

#include "GLEW/glew.h"

Shader::Shader(const ShaderType type, const ShaderSource& source)
    : m_Type{ type }, m_ShaderSource{ source }
{}

Shader::ShaderID Shader::SpawnShader() const noexcept
{
    const ShaderID id = glCreateShader(m_Type);

    const char* rawSource = m_ShaderSource.data();
    
    glShaderSource(id, 1, &rawSource, nullptr);

    glCompileShader(id);

    return id;
}

const Shader::ShaderSource& Shader::GetShaderSource()
    const noexcept
{
    return m_ShaderSource;
}

void Shader::SetShaderSource(const ShaderSource& source)
    noexcept
{
    m_ShaderSource = source;
}
