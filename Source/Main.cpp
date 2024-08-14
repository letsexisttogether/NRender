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

#include "VertexArray/VertexArray.hpp"
#include "AttributePointer/AttributePointer.hpp"
#include "GML/Vector/Definitions.hpp"
#include "FileReader/FileReader.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "TextureSpawn/TextureSpawner.hpp"
#include "Buffer/Buffer.hpp"
#include "Camera/Camera.hpp"

#include "FpsCounter/FpsCounter.hpp"

void ProcessInput(GLFWwindow* window);

void CheckOpenGLError(const char* functionName); 

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

    /*
    Camera camera{ { 0.0f, 0.0f }, halfWindowWidth, halfWindowHeight,
        firstProgram };
    */

    FpsCounter counter{};

    VertexArray vao{};

    using Triangle = Exeperimental::Buffer<GML::Vec2f, GL_ARRAY_BUFFER>;

    Triangle buffer 
    { 
        100, GL_DYNAMIC_DRAW 
    };

    AttributePointer firstPointer{ 0, 2, GL_FALSE, 4, 0 };
    AttributePointer secondPointer{ 1, 2, GL_FALSE, 4, 2 };

    const Triangle::ModernStorage triangle
    {
        { -0.5f, -0.5f }, { 0.0f, 0.0f },
        {  0.5f, -0.5f }, { 1.0f, 0.0f },
        {  0.0f,  0.5f }, { 0.5f, 0.5f }
    };
    buffer.UpdateData(triangle, 0);

    const Triangle::ModernStorage anotherTriangle 
    {
        { -0.9f, -0.9f }, { 0.0f, 0.0f },
        {  -0.3f, -0.9f }, { 1.0f, 0.0f }, 
        {  -0.6,  -0.6f }, { 0.5f, 0.5f }
    };
    buffer.UpdateData(anotherTriangle, 3 * 2);

    const Triangle::ModernStorage emptyTriangle
    (
        3 * 2, 
        { 0.0f, 0.0f }
    );

    bool isSeen = true;

    float timer = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        const float time = glfwGetTime();

        if (time - timer > 3.0f)
        {
            timer = time;

            isSeen = !isSeen;
            buffer.UpdateData(((isSeen) ? (anotherTriangle) : (emptyTriangle)),
                3 * 2);
        }

        const FpsCounter::FPS fps = counter.GetFPS();
        glfwSetWindowTitle(window, std::to_string(fps).c_str());

        glDrawArrays(GL_TRIANGLES, 0, 6);

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

void CheckOpenGLError(const char* functionName)
{
    for (GLenum err = glGetError(); err != GL_NO_ERROR; err = glGetError())
    {
        std::cerr << "OpenGL error in " 
            << ": " << err << std::endl;
    }
}

