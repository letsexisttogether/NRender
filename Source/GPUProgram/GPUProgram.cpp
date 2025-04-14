#include "GPUProgram.hpp"

#include "Core/Core.hpp"

GPUProgram::GPUProgram(Shader&& vertexShader, Shader&& fragmentShader,
    const bool shouldBind) noexcept
    : m_VertexShader{ std::move(vertexShader) },
    m_FragmentShader{ std::move(fragmentShader ) }
{
    Init(shouldBind); 
}

GPUProgram::~GPUProgram()
{
    glDeleteProgram(m_ID);
}

void GPUProgram::Bind() noexcept
{
    glUseProgram(m_ID);
}

void GPUProgram::Unbind() noexcept
{
    glUseProgram(m_ID);
}

void GPUProgram::Generate() noexcept
{
    m_ID = glCreateProgram();

    m_VertexShader.SetProgramID(m_ID);
    m_FragmentShader.SetProgramID(m_ID);

    m_VertexShader.Bind();
    m_FragmentShader.Bind();

    glLinkProgram(m_ID);
}
