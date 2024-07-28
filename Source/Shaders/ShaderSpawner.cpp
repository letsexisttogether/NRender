#include "ShaderSpawner.hpp"

#include "GLEW/glew.h"

ShaderSpawner::ShaderSpawner(const ShaderType type, const ShaderSource& source)
    : m_Type{ type }, m_ShaderSource{ source }
{}

ShaderSpawner::ShaderID ShaderSpawner::SpawnShader() const noexcept
{
    const ShaderID id = glCreateShader(m_Type);

    const char* rawSource = m_ShaderSource.data();
    
    glShaderSource(id, 1, &rawSource, nullptr);

    glCompileShader(id);

    return id;
}

const ShaderSpawner::ShaderSource& ShaderSpawner::GetShaderSource()
    const noexcept
{
    return m_ShaderSource;
}

void ShaderSpawner::SetShaderSource(const ShaderSource& source)
    noexcept
{
    m_ShaderSource = source;
}
