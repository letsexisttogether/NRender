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

#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"
#include "Experimental/Utility/Convert/GetGLType.hpp"
#include "Experimental/Vertex/ColorVertex.hpp"

using namespace NRender;

VertexArrayObject CreateSeparateVAO() noexcept;
VertexArrayObject CreateInstancedVAO() noexcept;
VertexArrayObject CreateVAOColorVertex() noexcept;

VertexArrayObject CreateGeneralInstance() noexcept;

std::vector<GML::Vec2f> CreateInstances() noexcept;

std::uint32_t CreateGPUProgram() noexcept;

std::vector<char> ReadShader(const std::string& fileName) noexcept;


std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1920, 1080 } };
    Render::Init();

    VertexArrayObject VAO{ CreateVAOColorVertex() };
    VAO.Bind();

    const std::uint32_t gpuProgram = CreateGPUProgram();
    glUseProgram(gpuProgram);

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

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

    VertexAttribPointer positionVAP
    {
        0, 2, GetGLType<GML::Vec2f>(), false, sizeof(GML::Vec3f), 0
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

    VertexAttribPointer colorVAP
    {
        1, 3, GetGLType<GML::Vec3f>(), false, sizeof(GML::Vec3f), 0
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

    VertexAttribPointer vap0
    {
        0, 2, GetGLType<float>(), false, 5 * sizeof(float), 0
    };
    
    VertexAttribPointer vap1
    {
        1, 3, GetGLType<float>(), false, 5 * sizeof(float), 2 * sizeof(float)
    };

    VertexBufferObject instancedVBO{ true };

    std::vector<GML::Vec2f> instances{ CreateInstances() };

    VertexAttribPointer vap2
    {
        2, 2, GetGLType<GML::Vec2f>(), false, sizeof(GML::Vec2f), 0
    };
    vap2.SetDivisor(1);

    instancedVBO.SetData(instances, GL_STATIC_DRAW);

    VAO.Unbind();

    return VAO;
}

VertexArrayObject CreateVAOColorVertex() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<ColorVertex> vertices
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

    VertexLayout<ColorVertex>::SpawnAttributes();

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

    VertexAttribPointer baseVAP
    {
        0, 2, GetGLType<GML::Vec2f>(), false, sizeof(GML::Vec2f), 0
    };

    const std::vector<GML::Vec2f> instancesData
    {
        CreateInstances()
    };

    VertexBufferObject instancesVBO{ true };
    instancesVBO.SetData(instancesData, GL_STATIC_DRAW);

    VertexAttribPointer instancesVAP
    {
        1, 2, GetGLType<GML::Vec2f>(), false, sizeof(GML::Vec2f), 0
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
