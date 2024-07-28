#include "GPUProgramCompiler.hpp"

#include "GLEW/glew.h"
#include "Shaders/ShaderSpawner.hpp"

GPUPRogramCompiler::GPUPRogramCompiler(ShaderSpawner&& vertexSpawner,
        ShaderSpawner&& fragmentSpawner)
    : m_VertextSpawner{ std::move(vertexSpawner) }, 
    m_FragmentSpawner{ std::move(fragmentSpawner) }
{}

GPUPRogramCompiler::ProgramID GPUPRogramCompiler::CompileProgram()
    const noexcept
{
    const ProgramID programID = glCreateProgram();
    
    const ShaderSpawner::ShaderID vertexID = 
        m_VertextSpawner.SpawnShader();
    const ShaderSpawner::ShaderID fragmentID = 
        m_FragmentSpawner.SpawnShader();

    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    
    glLinkProgram(programID);

    glDeleteShader(vertexID);    
    glDeleteShader(fragmentID);    

    return programID;
}
