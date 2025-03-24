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

#include "Experimental/Shape/Rectangle/Rectangle.hpp"
#include "Experimental/Sprite/Sprite.hpp"
#include "Experimental/Vertex/ColoredVertex.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"
#include "Experimental/Shape/Triangle/Triangle.hpp"
#include "Experimental/Sprite/Sprite.hpp"

using namespace NRender;

VertexArrayObject CreateVAO() noexcept;
std::uint32_t CreateGPUProgram() noexcept;

std::vector<char> ReadShader(const std::string& fileName) noexcept;

std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1920, 1080 } };
    Render::Init();

    std::unique_ptr<const Shape> triangle
    { 
        std::make_unique<Triangle>
        (
            ColoredVertex{ GML::Vec2f{ 0.0f, 0.5f },
                GML::Vec3f{ 1.0f, 0.0f, 0.0f } },
            ColoredVertex{ GML::Vec2f{ 0.5f, -0.5f },
                GML::Vec3f{ 0.0f, 1.0f, 0.0f } },
            ColoredVertex{ GML::Vec2f{ -0.5f, -0.5f },
                GML::Vec3f{ 0.0f, 0.0f, 1.0f } }
        )
    };

    std::unique_ptr<const Shape> rectangle 
    { 
        std::make_unique<Rectangle>
        (
            ColoredVertex{ GML::Vec2f{ -1.0f, 1.0f },
                GML::Vec3f{ 1.0f } }, 
            ColoredVertex{ GML::Vec2f{ 1.0f, 1.0f },
                GML::Vec3f{ 1.0f } },
            ColoredVertex{ GML::Vec2f{ 1.0f, -1.0f },
                GML::Vec3f{ 1.0f } },
            ColoredVertex{ GML::Vec2f{ -1.0f, -1.0f },
                GML::Vec3f{ 1.0f } }
        )
    };

    std::vector<Sprite> sprites{};
    sprites.reserve(2);

    sprites.push_back(Sprite{ *rectangle.get() });
    sprites.push_back(Sprite{ *triangle.get() });


    const std::uint32_t gpuProgram = CreateGPUProgram();

    const GML::Vec3f initialColor{ 1.0f };

    const std::int32_t realColorLocation = glGetUniformLocation
        (gpuProgram, "u_RealColor");

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(gpuProgram);

        const GML::Vec3f realColor{ initialColor * std::sin(time) };

        glUniform3f(realColorLocation, realColor.X(),
            realColor.Y(), realColor.Z());


        for (auto& sprite : sprites)
        {
            Render::DrawSprite(sprite);
        }

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

    std::unique_ptr<const Shape> triangle
    { 
        std::make_unique<Triangle>
        (
            ColoredVertex{ GML::Vec2f{ 0.0f, 0.5f },
                GML::Vec3f{ 1.0f, 0.0f, 0.0f } },
            ColoredVertex{ GML::Vec2f{ 0.5f, -0.5f },
                GML::Vec3f{ 0.0f, 1.0f, 0.0f } },
            ColoredVertex{ GML::Vec2f{ -0.5f, -0.5f },
                GML::Vec3f{ 0.0f, 0.0f, 1.0f } }
        )
    };
    
    VBO.SetData(triangle->GetVertices(), GL_STATIC_DRAW);
    EBO.SetData(triangle->GetIndices(), GL_STATIC_DRAW);

    VertexAttribPointer<float> vap0
    {
        0, 2, GL_FLOAT, false, 5, 0
    };

    VertexAttribPointer vap1
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
