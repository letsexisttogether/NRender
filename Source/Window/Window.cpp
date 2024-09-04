#include "Window.hpp"

#include <cassert>
#include <numeric>

Window::Window(const Title& title, const Resolution resolution)
    : m_Title{ title } 
{
    assert(glfwInit() && "Cannot initialize GLFW");

    m_BaseWindow = glfwCreateWindow(resolution.Width, resolution.Height,
        m_Title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_BaseWindow);
    glfwSwapInterval(0);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::ShouldClose() const noexcept
{
    return glfwWindowShouldClose(m_BaseWindow);
}

void Window::SwapBuffers() noexcept
{
    glfwSwapBuffers(m_BaseWindow);
}

const Window::Title& Window::GetTitle() const noexcept
{
    return m_Title;
}

void Window::SetTitle(const Title& title) noexcept
{
    m_Title = title;

    glfwSetWindowTitle(m_BaseWindow, m_Title.c_str());
}

Window::Dimension Window::GetWidth() const noexcept
{
    return GetResolution().Width;
}

void Window::SetWidth(const Dimension width) noexcept
{
    SetResolution({ width, GetHeight() }); 
}

Window::Dimension Window::GetHeight() const noexcept
{
    return GetResolution().Height;
}

void Window::SetHeight(const Dimension height) noexcept
{
    SetResolution({ GetWidth(), height });
}

Resolution Window::GetResolution() const noexcept
{
    Resolution resolution{}; 

    glfwGetWindowSize(m_BaseWindow, &resolution.Width, &resolution.Height);

    return resolution;
}

void Window::SetResolution(const Resolution resolution)
    noexcept
{
    glfwSetWindowSize(m_BaseWindow, resolution.Width, resolution.Height);
}


Resolution Window::GetAspectRatio() const noexcept
{
    const Resolution resolution{ GetResolution() };

    const Dimension gcd = std::gcd(resolution.Width, resolution.Height);

    return { resolution.Width / gcd, resolution.Height / gcd };
}

Window::AspectRatio Window::GetRelatedAspectRatio() const noexcept
{
    const Resolution resolution{ GetResolution() };

    return static_cast<AspectRatio>(resolution.Width) / resolution.Height;
}
