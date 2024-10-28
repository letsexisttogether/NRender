#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "Resolution.hpp"

NRenderSpaceStart

class Window
{
public:
    using Title = std::string;

    using Dimension = Resolution::Dimension;
    using AspectRatio = float;

public:
    static bool IsGLFWInit() noexcept;

public:
    Window() = delete;
    Window(const Window&) = delete;
    Window(Window&&) = delete;

    Window(const Title& title, const Resolution resolution);

    ~Window();

    bool ShouldClose() const noexcept;

    void SwapBuffers() noexcept;

    const Title& GetTitle() const noexcept;
    void SetTitle(const Title& title) noexcept;

    Dimension GetWidth() const noexcept;
    void SetWidth(const Dimension width) noexcept;

    Dimension GetHeight() const noexcept;
    void SetHeight(const Dimension height) noexcept;

    Resolution GetResolution() const noexcept; 
    void SetResolution(const Resolution resolution)
        noexcept;

    Resolution GetAspectRatio() const noexcept;
    AspectRatio GetRelatedAspectRatio() const noexcept;

    Window& operator = (const Window&) noexcept = delete;
    Window& operator = (Window&&) noexcept = delete;

private:
    static void InitGLFW() noexcept;

private:
    inline static bool s_IsGLFWInit{ false };
    
private:
    Title m_Title{}; 

    GLFWwindow* m_BaseWindow{};
};

NRenderSpaceEnd
