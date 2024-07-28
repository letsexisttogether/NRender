#pragma once

#include <cstdint>
#include <string>

class ShaderSpawner
{
public:
    using ShaderID = std::uint32_t;
    using ShaderType = std::uint32_t;
    using ShaderSource = std::string;

public:
    ShaderSpawner() = default;
    ShaderSpawner(const ShaderSpawner&) = default;
    ShaderSpawner(ShaderSpawner&&) = default;

    ShaderSpawner(const ShaderType type, const ShaderSource& source);

    ~ShaderSpawner() = default;

    ShaderID SpawnShader() const noexcept;

    const ShaderSource& GetShaderSource() const noexcept;
    void SetShaderSource(const ShaderSource& source) noexcept;

private:
    const ShaderType m_Type{};
    ShaderSource m_ShaderSource{};

};
