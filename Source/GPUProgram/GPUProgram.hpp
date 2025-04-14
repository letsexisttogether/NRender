#pragma once

#include "GPUProgram/Shader/Shader.hpp"

class GPUProgram : protected Boundable
{
public:
    GPUProgram() = delete;
    GPUProgram(const GPUProgram&) = delete;
    GPUProgram(GPUProgram&&) = default;

    GPUProgram(Shader&& vertexShader, Shader&& fragmentShader,
        const bool shouldBind) noexcept;

    ~GPUProgram();

    void Bind() noexcept override;
    void Unbind() noexcept override;

    GPUProgram& operator = (const GPUProgram&) = delete;
    GPUProgram& operator = (GPUProgram&&) = delete;

protected:
    void Generate() noexcept override;

private:
    Shader m_VertexShader;
    Shader m_FragmentShader;
};
