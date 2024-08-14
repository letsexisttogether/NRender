#pragma once

#include <GML/Matrix/Definitions.hpp>
#include <GML/Vector/Definitions.hpp>

#include "Basic/Boundable/Boundable.hpp"
#include "Basic/Shader/Shader.hpp"

class GPUProgram : public Boundable
{
public:
    using UniformName = const char*;
    using UniformLocation = std::int32_t;

public:
    GPUProgram() = delete;
    GPUProgram(const GPUProgram&) = delete;
    GPUProgram(GPUProgram&&) = delete;

    GPUProgram(Shader&& vertexSpawner, Shader&& fragmentSpawner,
        const bool shouldPrepare = true);

    ~GPUProgram();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    void Link() noexcept;

    void SetUniform(const UniformName name, const float value) noexcept;
    void SetUniform(const UniformName name, const std::int32_t value) noexcept;

    void SetUniform(const UniformName name, const GML::Vec3f& vector) noexcept;

    void SetUniform(const UniformName name, const GML::Mat4x4f& matrix) noexcept;

    GPUProgram& operator = (const GPUProgram&) noexcept
        = delete;
    GPUProgram& operator = (GPUProgram&&) noexcept
        = delete;

private:
    static inline BoundableID m_CurrentBoundID{};

protected:
    void Generate() noexcept override;

private:
    UniformLocation GetLocation(const UniformName name) const noexcept;

private:
    Shader m_VertextSpawner;
    Shader m_FragmentSpawner;
};
