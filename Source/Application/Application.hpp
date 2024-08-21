#pragma once

#include <memory>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Scene/Scene.hpp"

class Application
{
public:
    using ScenePtr = std::shared_ptr<Scene>;

public:
    static void Init() noexcept;
    static Application& GetApp() noexcept;
    static void CleanUp() noexcept;

public:
    void DoTheHardWork() noexcept;

    Scene* const GetScene() noexcept;
    GLFWwindow* const GetWindow() noexcept;

    void SetShouldContinue(const bool shouldContinue) noexcept;

private:
    Application() = default;
    Application(const Application&) = delete;
    Application(Application&&) = delete;

    ~Application() = default;

private:
    static Application* s_App;

private:
    GLFWwindow* m_Window{};

    ScenePtr m_Scene{};
    bool m_ShouldContinue{ true };
};
