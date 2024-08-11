#include <cstdint>
#include <cstdlib>
#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <GML/Variations/Transformation.hpp>
#include <GML/Variations/Projection.hpp>
#include <GML/Utility/Operations.hpp>

#include "FileReader/FileReader.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "TextureSpawn/TextureSpawner.hpp"
#include "Primitive/Square/Square.hpp"
#include "Camera/Camera.hpp"

#include "FpsCounter/FpsCounter.hpp"

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
    glfwSwapInterval(0);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 


    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;

        return EXIT_FAILURE;
    }

    if (argc < 2)
    {
        std::cerr << "The texture name were not provided" << std::endl;

        return EXIT_FAILURE;
    }

    const std::size_t objectCount = ((argc > 2) ? (std::atoi(argv[2])) : (1));

    /*
    VertexArray vao{};

    Vertex2DBuffer::Data vertexData{};

    for (std::size_t i = 0; i < objectCount; ++i)
    {
        vertexData.push_back({ -0.5f,  0.5f });
        vertexData.push_back({ 0.0f, 1.0f });

        vertexData.push_back({ 0.0f, 1.0f });
        vertexData.push_back({ 0.0f, 1.0f });

        vertexData.push_back({ -0.5f, -0.5f }); 
        vertexData.push_back({ 0.0f, 0.0f  });

        vertexData.push_back({  0.5f, -0.5f  }); 
        vertexData.push_back({ 1.0f, 0.0f  });
    }

    const Vertex2DBuffer buffer
    {
        std::move(vertexData)
    };

    IndexBuffer::Data indexData{};
    for (std::size_t i = 0; i < objectCount * 3; i += 3)
    {
        indexData.push_back(i);
        indexData.push_back(i + 1);
        indexData.push_back(i + 2);
    }

    const IndexBuffer indices
    {
        std::move(indexData)
    };

    AttributePointer firstPointer{ 0, 2, GL_FALSE, 4, 0 };
    AttributePointer secondPointer{ 1, 2, GL_FALSE, 4, 2 };
    */

    const TextureSpawner::TexturePath texturesPath
    {
        "D:/Projects/OPPL/Textures/"
    };

    TextureSpawner spawner{ TexFillParams{}, GL_TEXTURE0 };
 
    Texture firstTexture{ spawner.LoadTexture(texturesPath + argv[1]) };

    std::cout << "Hello, CloseGH again" << std::endl;

    const FileReader reader{};

    const std::string shadersPath
    {
        "D:/Projects/OPPL/Shaders/"
    };

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
    firstProgram.Bind();

    firstProgram.SetUniform("texture1", firstTexture.GetSlot());

    const float halfWindowWidth = windowWidth / 2.0f;
    const float halfWindowHeight = windowHeight / 2.0f;

    Camera camera{ { 0.0f, 0.0f }, halfWindowWidth, halfWindowHeight, firstProgram };

    FpsCounter counter{};

    std::vector<Square> squares{};

    for (std::size_t i = 0; i < objectCount; ++i)
    {
        squares.push_back(std::move(Square
            { { 0.0f + 200.0f * i, 0.0f }, 200.0f }));
    }

    // Square square{ { 0.0f, 0.0f }, 200.0f };

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        const FpsCounter::FPS fps = counter.GetFPS();
        glfwSetWindowTitle(window, std::to_string(fps).c_str());

        for (std::size_t i = 0; i < squares.size(); ++i)
        {
            squares[i].Draw();
        }

        camera.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}


// nastya 

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
