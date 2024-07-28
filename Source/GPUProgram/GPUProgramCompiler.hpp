#pragma once

#include "Shaders/ShaderSpawner.hpp"
#include <memory>
class GPUPRogramCompiler
{
public: 
    using ProgramID = std::uint32_t;

public:
    GPUPRogramCompiler() = delete;
    GPUPRogramCompiler(const GPUPRogramCompiler&) = delete;
    GPUPRogramCompiler(GPUPRogramCompiler&&) = default;

    GPUPRogramCompiler(ShaderSpawner&& vertexSpawner, 
        ShaderSpawner&& fragmentSpawner);

    ~GPUPRogramCompiler() = default;

    ProgramID CompileProgram() const noexcept;
    
    GPUPRogramCompiler& operator = (const GPUPRogramCompiler&) noexcept
        = delete;
    GPUPRogramCompiler& operator = (GPUPRogramCompiler&&) noexcept
        = delete;

private:
    ShaderSpawner m_VertextSpawner{};
    ShaderSpawner m_FragmentSpawner{};
};
