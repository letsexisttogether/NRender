#include "Shape/Triangle/Triangle.hpp"
#include "Sprite/Sprite.hpp"
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <GML/Variations/Transformation.hpp>
#include <GML/Variations/Projection.hpp>
#include <GML/Utility/Operations.hpp>
#include <GML/Vector/Definitions.hpp>

#include "Window/Window.hpp"
#include "Render/Render.hpp"
#include "Utility/FpsCounter/FpsCounter.hpp"

using namespace NRender;

// GLFWwindow* Initialize() noexcept;

void ProcessInput(GLFWwindow* window);

void CheckOpenGLError(const char* functionName); 

std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1400, 800 } };
    Render::Init();

    std::cout << std::boolalpha << Window::IsGLFWInit() << std::endl;

    // Sprite sprite{ Triangle{ {}, {}, {} }, Triangle{ {}, {}, {} }, 0, 0 };

    FpsCounter counter{};

    const Resolution aspectRatio = window.GetAspectRatio();

    std::cout << "The aspect ratio is " << aspectRatio.Width << ' '
        << aspectRatio.Height << '\n'; 

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        const FpsCounter::FPS fps = counter.GetFPS();
        window.SetTitle(std::to_string(fps));

        glClear(GL_COLOR_BUFFER_BIT);

        window.SwapBuffers();

        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

// nastya 

/*
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
*/

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
