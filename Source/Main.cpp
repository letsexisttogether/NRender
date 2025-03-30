#include <cstdlib>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>
#include <chrono>

#include <GML/Vector/Definitions.hpp>
#include <yvals.h>

#include "Core/Core.hpp"
#include "GLFW/glfw3.h"
#include "Render/Render.hpp"
#include "Window/Window.hpp"

#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"
#include "Experimental/Utility/Convert/GetGLType.hpp"
#include "Experimental/Vertex/ColorVertex.hpp"
#include "Experimental/Instance/InstanceSource.hpp"
#include "Experimental/Sprite/Sprite.hpp"
#include "Experimental/Vertex/ComplexVertex.hpp"
#include "Experimental/Vertex/Vertex.hpp"
#include "Experimental/Instance/Manger/InstanceManager.hpp"
#include "Experimental/GPUProgram/GPUProgram.hpp"

using namespace NRender;

VertexArrayObject CreateSeparateVAO() noexcept;
VertexArrayObject CreateInstancedVAO() noexcept;
VertexArrayObject CreateVAOColorVertex() noexcept;

VertexArrayObject CreateScaledInstance() noexcept;

std::vector<GML::Vec2f> CreateInstances() noexcept;

GPUProgram CreateModernGPUProgram() noexcept;
std::uint32_t CreateGPUProgram() noexcept;

std::vector<char> ReadShader(const std::string& fileName) noexcept;


std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1920, 1080 } };
    Render::Init();

    const std::vector<ColorVertex> baseData
    {
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },   
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f } }
    };

    std::vector<ComplexVertex> instances
    {
        { { 0.0f,  0.5f },  0.5f },
        { { 0.0f, -0.5f },  0.5f },
        { { 0.5f, 0.0f },   0.5f },
        { { -0.5f, 0.0f },  0.5f },
    };

    InstanceSource<ColorVertex, ComplexVertex> instanceSource
    {
        baseData, std::move(instances)
    }; 

    /*
    InstanceManager manager{};

    const std::int32_t id = manager.AddInstance(std::move(instanceSource));
    auto& aquiredInstance = manager.GetInstance<ColorVertex, ComplexVertex>(id);
    */

    /*
    const std::uint32_t gpuProgram = CreateGPUProgram();
    glUseProgram(gpuProgram);
    */

    GPUProgram gpuProgram{ CreateModernGPUProgram() };
    gpuProgram.Bind();

    float animationStart = glfwGetTime();
    float animationMultiplier = 1.0f;

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        if (const float passedTime = time - animationStart;
            passedTime > 2.0f)
        {
            auto instance = instanceSource.GetInstance(3);
            instance.Position.X() += 0.5 * animationMultiplier; 

            instanceSource.SetInstance(3, std::move(instance));

            animationMultiplier = -animationMultiplier;
            animationStart = time;
        }


        glClear(GL_COLOR_BUFFER_BIT);

        instanceSource.GetVAO().Bind();

        glDrawArraysInstanced(GL_TRIANGLES, 0,
            instanceSource.GetBaseSize(), instanceSource.GetInstancesSize());

        /*
        triangles.GetVAO().Bind();
        glDrawArrays(GL_TRIANGLES, 0, triangles.GetVerticesSize());
        */


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

VertexArrayObject CreateScaledInstance() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<ColorVertex> baseData
    {
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },   
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f } }
    };

    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(baseData, GL_STATIC_DRAW);

    auto baseAttributes = VertexLayout<ColorVertex>::SpawnAttributes();

    const std::vector<ComplexVertex> instancesData
    {
        { { 0.0f,  0.5f },  0.5f },
        { { 0.0f, -0.5f },  0.5f },
        { { 0.5f, 0.0f },   0.5f },
        { { -0.5f, 0.0f },  0.5f },
    };

    VertexBufferObject instancesVBO{ true };
    instancesVBO.SetData(instancesData, GL_STATIC_DRAW);

    auto attributes = VertexLayout<ComplexVertex>::SpawnAttributes(2);

    for (auto& attribute : attributes)
    {
        attribute.SetDivisor(1);
    }

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


GPUProgram CreateModernGPUProgram() noexcept
{
    Shader vertexShader{ GL_VERTEX_SHADER, "shader.vert" };
    Shader fragmentShader{ GL_FRAGMENT_SHADER, "shader.frag" };

    GPUProgram gpuProgram
    { 
        std::move(vertexShader),
        std::move(fragmentShader),
        false
    };

    return gpuProgram;
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
