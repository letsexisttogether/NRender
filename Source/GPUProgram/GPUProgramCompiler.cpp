#include "GPUProgramCompiler.hpp"

#include "GLEW/glew.h"
#include "Boundable/Boundable.hpp"
#include "Shaders/ShaderSpawner.hpp"

GPUProgram::GPUProgram(Shader&& vertexSpawner,
    Shader&& fragmentSpawner)
    : Boundable{ GL_PROGRAM }, m_VertextSpawner{ std::move(vertexSpawner) },
    m_FragmentSpawner{ std::move(fragmentSpawner) }
{
    Generate();
}

void GPUProgram::CompileProgram()
    const noexcept
{
    const ProgramID programID = glCreateProgram();
    
    const Shader::ShaderID vertexID = 
        m_VertextSpawner.SpawnShader();
    const Shader::ShaderID fragmentID = 
        m_FragmentSpawner.SpawnShader();

    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    
    glLinkProgram(programID);

    glDeleteShader(vertexID);    
    glDeleteShader(fragmentID);    

    return programID;
}

void GPUProgram::Generate() noexcept
{
    m_ID = glCreateProgram(); 

    const Shader::ShaderID vertexID = 
        m_VertextSpawner.SpawnShader();
    const Shader::ShaderID fragmentID = 
        m_FragmentSpawner.SpawnShader();
}
