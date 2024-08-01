#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "STB/stb_image.h"

#include "Buffer/VertexBuffer.hpp"
#include "Buffer/IndexBuffer.hpp"
#include "FileReader/FileReader.hpp"
#include "VertexArray/VertexArray.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "TextureSpawn/TextureSpawner.hpp"
#include "AttributePointer/AttributePointer.hpp"

std::int32_t main(std::int32_t argc, char** argv)
{
    if (!glfwInit())
    {
        std::cerr << "Can't initialize GLFW" << std::endl;

        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 600, "CloseGH",
        nullptr, nullptr);

    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;

        return EXIT_FAILURE;
    }

    const TextureSpawner::TexturePath texturesPath
    {
        "D:/Projects/OPPL/Textures/"
    };

    TextureSpawner spawner{ TexFillParams{}, GL_TEXTURE0 };

    if (argc < 3)
    {
        std::cerr << "The textures' names were not provided" << std::endl;

        return EXIT_FAILURE;
    }
    
    Texture firstTexture{ spawner.LoadTexture(texturesPath + argv[1]) };
    Texture secondTexture{ spawner.LoadTexture(texturesPath + argv[2]) };

    std::cout << "Hello, CloseGH again" << std::endl;

    FileReader reader{};

    const std::string shadersPath
    {
        "D:/Projects/OPPL/Shaders/"
    };

    VertexArray firstTriangle{};

    VertexBuffer firstVertecies 
    { 
        {
            -0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f
        }
    };

    IndexBuffer firstIndices
    {
        {
            0, 1, 2,
            1, 2, 3
        }
    };

    AttributePointer firstAttribPointer{ 0, 3, GL_FALSE, 8, 0 };
    AttributePointer secondAttribPointer{ 1, 3, GL_FALSE, 8, 3 };
    AttributePointer thirdAttribPointer{ 2, 2, GL_FALSE, 8, 6 };

    Shader firstVertexShader
    {
        GL_VERTEX_SHADER,
        reader.Read(shadersPath + "Default.vert")
    };
    Shader firstFragmenShader 
    {
        GL_FRAGMENT_SHADER,
        reader.Read(shadersPath + "Default.frag")
    };

    GPUProgram firstProgram 
    { 
        std::move(firstVertexShader),
        std::move(firstFragmenShader)
    };

    const float secondStrength = ((argc > 3) ? (std::atof(argv[3])) : (0.5));

    while (!glfwWindowShouldClose(window))
    {
        // glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        const float timeValue = glfwGetTime();
        const float offset = (std::sin(timeValue));

        firstProgram.Bind();

        firstProgram.SetUniform("offset", { offset, 0.0f, 0.0f });

        firstProgram.SetUniform("texture1", firstTexture.GetSlot());
        firstProgram.SetUniform("texture2", secondTexture.GetSlot());

        firstProgram.SetUniform("secondStrength", secondStrength);

        firstTexture.Bind();
        secondTexture.Bind();

        firstTriangle.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}
