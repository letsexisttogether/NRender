#include <cassert>
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
#include "GML/Vector/Definitions.hpp"

#include "Application/Application.hpp"
#include "Basic/GPUProgram/GPUProgram.hpp"
#include "Basic/AttributePointer/AttributePointer.hpp"
#include "Basic/VertexArray/VertexArray.hpp"
#include "Basic/Buffer/IndexBuffer.hpp"
#include "Basic/Buffer/VertexBuffer.hpp"
#include "Utility/FileReader/FileReader.hpp"
#include "Utility/TextureSpawn/TextureSpawner.hpp"
#include "Utility/FpsCounter/FpsCounter.hpp"

GLFWwindow* Initialize() noexcept;

void ProcessInput(GLFWwindow* window);

void CheckOpenGLError(const char* functionName); 

const Texture::Resolution windowWidth = 1400;
const Texture::Resolution windowHeight = 800;

std::int32_t main(std::int32_t argc, char** argv)
{
    Application::Init();

    GLFWwindow* window = Application::GetApp().GetWindow(); 

    if (!window)
    {
        return EXIT_FAILURE;
    }

    if (argc < 2)
    {
        std::cerr << "The texture name were not provided" << std::endl;

        return EXIT_FAILURE;
    }

    const Vertex2DBuffer::Count objectsCount = 
        ((argc > 2) ? (std::atoi(argv[2])) : (1));

    TextureSpawner spawner{ TexFillParams{}, GL_TEXTURE0 };

    Texture firstTexture{ spawner.LoadTexture(argv[1]) };

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

    firstProgram.SetUniform("texture1", firstTexture.GetSlot());

    const float halfWindowWidth = windowWidth / 2.0f;
    const float halfWindowHeight = windowHeight / 2.0f;

    FpsCounter counter{};

    while (!glfwWindowShouldClose(window))
    {
        const float time = glfwGetTime();

        ProcessInput(window);

        const FpsCounter::FPS fps = counter.GetFPS();
        glfwSetWindowTitle(window, std::to_string(fps).c_str());

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    Application::CleanUp();
    
    return EXIT_SUCCESS;
}

// nastya 


GLFWwindow* Initialize() noexcept
{
    if (!glfwInit())
    {
        std::cerr << "Can't initialize GLFW" << std::endl;

        return nullptr;
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

        return nullptr;
    }

    return window;
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void CheckOpenGLError(const char* functionName)
{
    for (GLenum err = glGetError(); err != GL_NO_ERROR; err = glGetError())
    {
        std::cerr << "OpenGL error in " 
            << ": " << err << std::endl;
    }
}
