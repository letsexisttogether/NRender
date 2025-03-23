#include <cstdlib>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>

#include <GML/Vector/Definitions.hpp>

#include "Render/Render.hpp"
#include "Window/Window.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"

using namespace NRender;

VertexArrayObject CreateVAO() noexcept;
std::uint32_t CreateGPUProgram() noexcept;

std::vector<char> ReadShader(const std::string& fileName) noexcept;

std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1400, 800 } };
    Render::Init();

    VertexArrayObject VAO{ CreateVAO() };

    const std::uint32_t gpuProgram = CreateGPUProgram();

    const GML::Vec3f initialColor{ 1.0f };

    const std::int32_t realColorLocation = glGetUniformLocation
        (gpuProgram, "u_RealColor");


    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        VAO.Bind();

        glUseProgram(gpuProgram);

        const GML::Vec3f realColor{ initialColor * std::sin(time) };

        glUniform3f(realColorLocation, realColor.X(),
            realColor.Y(), realColor.Z());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.SwapBuffers();

        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

// nastya 

VertexArrayObject CreateVAO() noexcept
{
    VertexArrayObject VAO{ true };

    VertexBufferObject VBO{ true };
    ElementBufferObject EBO{ true };

    const std::vector<float> vertices
    {
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        0.0f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,    0.0f, 0.0f, 1.0f
    };

    const std::vector<std::int32_t> indices
    {
        0, 1, 2,
    };

    VBO.SetData(vertices, GL_STATIC_DRAW);
    EBO.SetData(indices, GL_STATIC_DRAW); 

    VertexAttribPointer<float> vap0
    {
        0, 2, GL_FLOAT, false, 5, 0
    };

    VertexAttribPointer<float> vap1
    {
        vap0.SpawnNext(3)
    };

    VAO.Unbind();

    return VAO;
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
