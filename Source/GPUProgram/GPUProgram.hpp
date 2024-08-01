#pragma once

#include <memory>

#include "Boundable/Boundable.hpp"
#include "Shader/Shader.hpp"
#include "Vector/Vector.hpp"

class GPUProgram : public Boundable
{
public:
    using UniformName = const char*;
    using UniformLocation = std::int32_t;

public:
    GPUProgram() = delete;
    GPUProgram(const GPUProgram&) = delete;
    GPUProgram(GPUProgram&&) = default;

    GPUProgram(Shader&& vertexSpawner, Shader&& fragmentSpawner,
        const bool shouldPrepare = true);

    ~GPUProgram() = default;

    void Bind() noexcept override;
    void UnBind() noexcept override;

    void Link() noexcept;

    void SetUniform(const UniformName name, const float value) noexcept;
    void SetUniform(const UniformName name, const std::int32_t value) noexcept;

    void SetUniform(const UniformName name, const Vector& vector) noexcept;

    GPUProgram& operator = (const GPUProgram&) noexcept
        = delete;
    GPUProgram& operator = (GPUProgram&&) noexcept
        = delete;

protected:
    void Generate() noexcept override;

private:
    UniformLocation GetLocation(const UniformName name) const noexcept;

private:
    Shader m_VertextSpawner;
    Shader m_FragmentSpawner;
};
