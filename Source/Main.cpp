#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <GML/Matrix/Matrix.hpp>
#include <GML/Variations/Transformation.hpp>
#include <GML/Variations/Projection.hpp>
#include <GML/Utility/Operations.hpp>

#include "Buffer/VertexBuffer.hpp"
#include "Buffer/IndexBuffer.hpp"
#include "FileReader/FileReader.hpp"
#include "VertexArray/VertexArray.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "TextureSpawn/TextureSpawner.hpp"
#include "AttributePointer/AttributePointer.hpp"

void ProcessInput(GLFWwindow* window);

const Texture::Resolution windowWidth = 1400;
const Texture::Resolution windowHeight = 800;

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

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CloseGH",
        nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

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

    const FileReader reader{};

    const std::string shadersPath
    {
        "D:/Projects/OPPL/Shaders/"
    };

    VertexArray firstTriangle{};

    VertexBuffer firstVertecies 
    { 
        {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        }
    };

    AttributePointer firstAttribPointer{ 0, 3, GL_FALSE, 5, 0 };
    AttributePointer secondAttribPointer{ 1, 2, GL_FALSE, 5, 3 };

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


    // glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        const float time = glfwGetTime();

        ProcessInput(window);
        // glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        firstProgram.Bind();

        firstProgram.SetUniform("texture1", firstTexture.GetSlot());
        firstProgram.SetUniform("texture2", secondTexture.GetSlot());
        firstProgram.SetUniform("secondStrength", secondStrength);

        firstTexture.Bind();
        secondTexture.Bind();

        firstTriangle.Bind();

        const Mat4x4f model{ GetRotation(time * ConvertToRadians(50.0f),
            Vec3f{ 0.5f, 1.0f, 0.0f }) };
        firstProgram.SetUniform("model", model);

        const Mat4x4f view{ GetTranslation(Vec3f{ 0.0f, 0.0f, -3.0f }) };
        firstProgram.SetUniform("view", view);

        const Mat4x4f projection{ GetPerspective(ConvertToRadians(45.0f),
                static_cast<float>(windowWidth) / windowHeight, 0.1f, 100.0f) };
        firstProgram.SetUniform("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

}
