#include "GPUProgram.hpp"

#include "GLEW/glew.h"
#include "Shaders/Shader.hpp"

GPUProgram::GPUProgram(Shader&& vertexSpawner, Shader&& fragmentSpawner)
    : m_VertextSpawner{ std::move(vertexSpawner) },
    m_FragmentSpawner{ std::move(fragmentSpawner) }
{
    Generate();

    m_VertextSpawner.SetProgramID(m_ID);
    m_FragmentSpawner.SetProgramID(m_ID);
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

void GPUProgram::Generate() noexcept
{
    m_ID = glCreateProgram(); 
}
