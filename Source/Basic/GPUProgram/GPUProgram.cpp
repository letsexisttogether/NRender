#include "GPUProgram.hpp"

#include <GL/glew.h>

GPUProgram::GPUProgram(Shader&& vertexSpawner, Shader&& fragmentSpawner,
    const bool shouldPrepare)
    : m_VertextSpawner{ std::move(vertexSpawner) },
    m_FragmentSpawner{ std::move(fragmentSpawner) }
{
    Generate();

    m_VertextSpawner.SetProgramID(m_ID);
    m_FragmentSpawner.SetProgramID(m_ID);

    if (shouldPrepare)
    {
        Link();

        Bind();
    }
}

GPUProgram::~GPUProgram()
{
    glDeleteProgram(m_ID);
}

void GPUProgram::Bind() noexcept
{
    if (m_ID != m_CurrentBoundID)
    {
        glUseProgram(m_ID);

        m_CurrentBoundID = m_ID;
    }
}

void GPUProgram::UnBind() noexcept
{
    glUseProgram(0);
}

void GPUProgram::Link() noexcept
{
    m_VertextSpawner.Bind();
    m_FragmentSpawner.Bind();

    glLinkProgram(m_ID);
}

void GPUProgram::SetUniform(const UniformName name, const float value)
    noexcept
{
    const UniformLocation location = GetLocation(name);

    glUniform1f(location, value);
}

void GPUProgram::SetUniform(const UniformName name, const std::int32_t value)
    noexcept
{
    const UniformLocation location = GetLocation(name);

    glUniform1i(location, value);
}

void GPUProgram::SetUniform(const UniformName name, const GML::Vec3f& vector)
    noexcept
{
    const UniformLocation location = GetLocation(name);

    glUniform3f(location, vector.X(), vector.Y(), vector.Z());
}

void GPUProgram::SetUniform(const UniformName name, const GML::Mat4x4f& matrix)
    noexcept
{
    const UniformLocation location = GetLocation(name);

    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.GetDataPointer());
}

void GPUProgram::Generate() noexcept
{
    m_ID = glCreateProgram(); 
}

GPUProgram::UniformLocation GPUProgram::GetLocation(const UniformName name)
    const noexcept
{
    return glGetUniformLocation(m_ID, name);
}

