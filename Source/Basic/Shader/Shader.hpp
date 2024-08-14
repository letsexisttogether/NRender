#pragma once

#include <string>

#include "Basic/Boundable/Boundable.hpp"

class Shader : public Boundable
{
public:
    using ShaderSource = std::string;

public:
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader(Shader&&) = default;

    Shader(const Type type, const ShaderSource& source, 
        const bool shouldPrepare = true);

    ~Shader();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    void Compile() noexcept;

    const ShaderSource& GetShaderSource() const noexcept;
    void SetShaderSource(const ShaderSource& source) noexcept;
    
    BoundableID GetProgramID() const noexcept;
    void SetProgramID(const BoundableID programID) noexcept;

    Shader& operator = (const Shader&) noexcept = delete;
    Shader& operator = (Shader&&) noexcept = delete;

protected:
    void Generate() noexcept override;

private:
    ShaderSource m_ShaderSource{};
    BoundableID m_ProgramID{};
};
