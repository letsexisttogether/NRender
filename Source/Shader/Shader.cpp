#include "Shader.hpp"

#include "Boundable/Boundable.hpp"
#include "GLEW/glew.h"

Shader::Shader(const Type type, const ShaderSource& source,
    const bool shouldPrepare)
    : Boundable{ type }, m_ShaderSource{ source }
{
    Generate();

    if (shouldPrepare)
    {
        Compile();
    }
}

Shader::~Shader()
{
    UnBind();

    glDeleteShader(m_ID);
}

void Shader::Bind() noexcept
{
    glAttachShader(m_ProgramID, m_ID);
}

void Shader::UnBind() noexcept
{
    glDetachShader(m_ProgramID, m_ID);
}

void Shader::Compile() noexcept
{
    const char* rawSource = m_ShaderSource.data();

    glShaderSource(m_ID, 1, &rawSource, nullptr);

    glCompileShader(m_ID);
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

Shader::BoundableID Shader::GetProgramID() const noexcept
{
    return m_ProgramID;
}

void Shader::SetProgramID(const BoundableID programID) noexcept
{
    m_ProgramID = programID;
}

void Shader::Generate() noexcept
{
    m_ID = glCreateShader(m_Type);
}
