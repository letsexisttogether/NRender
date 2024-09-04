#include "Application.hpp"

#include <iostream>
#include <cassert>

void Application::Init() noexcept
{
    s_App = new Application{};

    if (!glfwInit())
    {
        std::cerr << "Can't initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    s_App->m_Window = glfwCreateWindow(1400, 800, "CloseGH",
        nullptr, nullptr);

    glfwMakeContextCurrent(s_App->m_Window);
    glfwSwapInterval(0);

    glfwSetInputMode(s_App->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
    }


    s_App->m_Scene.reset();
}

Application& Application::GetApp() noexcept
{
    assert(s_App && "The app was not initialized");

    return *s_App;
}

void Application::CleanUp() noexcept
{
    glfwTerminate();

    delete s_App;
}

void Application::DoTheHardWork() noexcept
{
    while(m_ShouldContinue && !glfwWindowShouldClose(m_Window))
    {
    }
}

Application::Scene* const Application::GetScene() noexcept
{
    return m_Scene.get();
}

GLFWwindow* const Application::GetWindow() noexcept
{
    return m_Window;
}

void Application::SetShouldContinue(const bool shouldContinue) noexcept
{
    m_ShouldContinue = shouldContinue;
}


Application* Application::s_App{};
