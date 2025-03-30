#include "Shader.hpp"
#include "Core/Core.hpp"

#include <cassert>
#include <fstream>

Shader::Shader(const GLenum type, Code&& code) noexcept
    : m_Type{ type }, m_Code{ std::move(code) }
{
    Init(false);
}

Shader::Shader(const GLenum type, const std::filesystem::path& path) noexcept
    : m_Type{ type }
{
    ReadCodeFromFile(path);

    Init(false);
}

Shader::~Shader()
{
    glDeleteShader(m_ID);
}

void Shader::Bind() noexcept
{
    assert(m_ProgramID != 0 && "[Shader::Generate] The program ID is invalid");

    glAttachShader(m_ProgramID, m_ID);
}

void Shader::Unbind() noexcept
{
    assert(m_ProgramID != 0 && "[Shader::Generate] The program ID is invalid");

    glDetachShader(m_ProgramID, m_ID);
}

std::uint32_t Shader::GetProgramID() const noexcept
{
    return m_ProgramID;
}

void Shader::SetProgramID(const std::uint32_t programID) noexcept
{
    m_ProgramID = programID;
}

GLenum Shader::GetType() const noexcept
{
    return m_Type;
}

void Shader::Generate() noexcept
{
    m_ID = glCreateShader(m_Type);

    const char* code = m_Code.data();

    glShaderSource(m_ID, 1, &code, nullptr);
    glCompileShader(m_ID);
}

// SUGGESTION: Use a file reader
void Shader::ReadCodeFromFile(const std::filesystem::path& path) noexcept
{
    assert(std::filesystem::exists(path) && "File does not exist");

    std::ifstream inputStream{ path };

    inputStream.seekg(0, std::ios::end);
    const std::streamsize fileSize = inputStream.tellg();
    inputStream.seekg(0, std::ios::beg);

    m_Code.resize(fileSize);

    inputStream.read(m_Code.data(), fileSize);
}
