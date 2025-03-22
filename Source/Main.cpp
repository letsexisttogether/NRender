#include <iostream>
#include <thread>

#include "Render/Render.hpp"
#include "Window/Window.hpp"

using namespace NRender;

// GLFWwindow* Initialize() noexcept;

void ProcessInput(GLFWwindow* window);

void CheckOpenGLError(const char* functionName); 

std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1400, 800 } };
    Render::Init();

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        window.SetTitle("Hello");

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
