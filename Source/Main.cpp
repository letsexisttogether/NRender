#include <cstdlib>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>

#include <GML/Vector/Definitions.hpp>

#include "Core/Core.hpp"
#include "Render/Render.hpp"
#include "Window/Window.hpp"

#include "Experimental/Instance/Instance.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"

using namespace NRender;

VertexArrayObject CreateSeparateVAO() noexcept;
VertexArrayObject CreateInstancedVAO() noexcept;
Instance<GML::Vec2f> CreateInstance() noexcept;
VertexArrayObject DisposeComplexVertex() noexcept;

VertexArrayObject CreateGeneralInstance() noexcept;

std::vector<GML::Vec2f> CreateInstances() noexcept;

std::uint32_t CreateGPUProgram() noexcept;

std::vector<char> ReadShader(const std::string& fileName) noexcept;


std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1920, 1080 } };
    Render::Init();

    VertexArrayObject VAO{ CreateGeneralInstance() };
    VAO.Bind();

    const std::uint32_t gpuProgram = CreateGPUProgram();
    glUseProgram(gpuProgram);

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

        window.SwapBuffers();

        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

// nastya 


VertexArrayObject CreateSeparateVAO() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<GML::Vec2f> positions
    {
        { -0.5f,  0.5f },
        { 0.5f, -0.5f },
        { -0.5f, -0.5f },

        { -0.5f,  0.5f }, 
        { 0.5f, -0.5f },
        { 0.5f,  0.5f }
    };

    VertexBufferObject positionVBO{ true };
    positionVBO.SetData(positions, GL_STATIC_DRAW);

    VertexAttribPointer<GML::Vec2f> positionVAP
    {
        0, 2, false, 1, 0
    };

    const std::vector<GML::Vec3f> colors
    {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f },

        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 1.0f }
    };

    VertexBufferObject colorVBO{ true };
    colorVBO.SetData(colors, GL_STATIC_DRAW); 

    VertexAttribPointer<GML::Vec3f> colorVAP
    {
        1, 3, false, 1, 0
    };

    VAO.Unbind();

    return VAO;
}

VertexArrayObject CreateInstancedVAO() noexcept
{
    VertexArrayObject VAO{ true };

    VertexBufferObject baseVBO{ true };

    const std::vector<float> vertices
    {
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
        0.05f,  0.05f,  0.0f, 1.0f, 1.0f	
    };

    baseVBO.SetData(vertices, GL_STATIC_DRAW);

    VertexAttribPointer<float> vap0
    {
        0, 2, false, 5 * sizeof(float), 0
    };
    
    VertexAttribPointer<float> vap1
    {
        1, 3, false, 5 * sizeof(float), 2 * sizeof(float)
    };

    VertexBufferObject instancedVBO{ true };

    std::vector<GML::Vec2f> instances{ CreateInstances() };

    VertexAttribPointer<GML::Vec2f> vap2
    {
        2, 2, false, sizeof(GML::Vec2f), 0
    };
    vap2.SetDivisor(1);

    instancedVBO.SetData(instances, GL_STATIC_DRAW);

    VAO.Unbind();

    return VAO;
}

Instance<GML::Vec2f> CreateInstance() noexcept
{
    const std::vector<float> vertices
    {
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
        0.05f,  0.05f,  0.0f, 1.0f, 1.0f	
    };

    std::vector<GML::Vec2f> offsets{ CreateInstances() };

    Instance<GML::Vec2f> instance{ vertices, offsets };

    return instance;
}


struct ComplexVertex
{
    GML::Vec2f Position{};
    GML::Vec3f Color{};
};

VertexArrayObject DisposeComplexVertex() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<ComplexVertex> vertices
    {
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },   
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f } }
    };
    
    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(vertices, GL_STATIC_DRAW);

    VertexAttribPointer<GML::Vec2f> positionVAP
    {
        0, 2, false, sizeof(ComplexVertex), 0
    };

    VertexAttribPointer<GML::Vec3f>
    {
        1, 3, false, sizeof(ComplexVertex), sizeof(GML::Vec2f)
    };

    VAO.Unbind();

    return VAO;
}

VertexArrayObject CreateGeneralInstance() noexcept
{
    struct InstanceObject
    {
        GML::Vec2f Position{};
        float Scale{};
    };


    VertexArrayObject VAO{ true };

    const std::vector<GML::Vec2f> baseData
    {
        { -0.05f,  0.05f },
        { 0.05f, -0.05f },
        { -0.05f, -0.05f },

        { -0.05f,  0.05f }, 
        { 0.05f, -0.05f },
        { 0.05f,  0.05f }
    };

    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(baseData, GL_STATIC_DRAW);

    // SUGGESTION: VertexAttribPointer::_DataType is useless

    VertexAttribPointer<GML::Vec2f> baseVAP
    {
        0, 2, false, sizeof(GML::Vec2f), 0
    };

    const std::vector<GML::Vec2f> instancesData
    {
        CreateInstances()
    };

    VertexBufferObject instancesVBO{ true };
    instancesVBO.SetData(instancesData, GL_STATIC_DRAW);

    VertexAttribPointer<GML::Vec2f> instancesVAP
    {
        1, 2, false, sizeof(GML::Vec2f), 0
    };
    instancesVAP.SetDivisor(1);

    VAO.Unbind();

    return VAO;
};

std::vector<GML::Vec2f> CreateInstances() noexcept
{
    std::vector<GML::Vec2f> offsets{};
    offsets.reserve(100);

    const float shift = 0.1f;

    for (std::int32_t y = -10; y < 10; y += 2)
    {
        for (std::int32_t x = -10; x < 10; x += 2)
        {
            GML::Vec2f offset
            {
                static_cast<float>(x) / 10.0f + shift,
                static_cast<float>(y) / 10.0f + shift
            };

            offsets.push_back(std::move(offset));
        }
    }
    
    return offsets;
}

std::uint32_t CreateGPUProgram() noexcept
{
    const std::uint32_t gpuProgram = glCreateProgram();

    const auto vertexShaderSource = ReadShader("shader.vert");
    const char* vertexShaderData = vertexShaderSource.data();

    const std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderData, nullptr);
    glCompileShader(vertexShader);

    const auto fragmentShaderSource = ReadShader("shader.frag");
    const char* fragmentShaderData = fragmentShaderSource.data();

    const std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderData, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(gpuProgram, vertexShader);
    glAttachShader(gpuProgram, fragmentShader);

    glLinkProgram(gpuProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return gpuProgram;
}

std::vector<char> ReadShader(const std::string& fileName) noexcept
{
    assert(std::filesystem::exists(fileName) && "File does not exist");

    std::vector<char> shader{};

    std::ifstream inputStream{ fileName };

    inputStream.seekg(0, std::ios::end);
    const std::streamsize fileSize = inputStream.tellg();
    inputStream.seekg(0, std::ios::beg);

    shader.resize(fileSize);

    inputStream.read(shader.data(), fileSize);

    return shader;
}
