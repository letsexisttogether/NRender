#include "GPUProgram.hpp"

#include "GLEW/glew.h"

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

void GPUProgram::Bind() noexcept
{
    glUseProgram(m_ID);
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

void GPUProgram::SetUniform(const UniformName name, const Vector& vector)
    noexcept
{
    const UniformLocation location = GetLocation(name);

    glUniform3f(location, vector.X, vector.Y, vector.Z);
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

