#pragma once

#include <filesystem>
#include <string_view>

#include "Core/Core.hpp"
#include "Experimental/Boundable/Boundable.hpp"

class Shader : protected Boundable
{
public:
    using Code = std::vector<char>;

public:
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader(Shader&&) = default;

    Shader(const GLenum type, Code&& code) noexcept;
    Shader(const GLenum type, const std::filesystem::path& path) noexcept;

    ~Shader();

    void Bind() noexcept override;
    void Unbind() noexcept override;

    std::uint32_t GetProgramID() const noexcept;
    void SetProgramID(const std::uint32_t programID) noexcept;

    GLenum GetType() const noexcept;

    Shader& operator = (const Shader&) = delete;
    Shader& operator = (Shader&&) = delete;

protected:
    void Generate() noexcept override;

private:
    void ReadCodeFromFile(const std::filesystem::path& path) noexcept;

private:
    std::uint32_t m_ProgramID{};

    GLenum m_Type;
    Code m_Code;
};
