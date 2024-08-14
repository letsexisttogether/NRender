#include "FpsCounter.hpp"

#include <GLFW/glfw3.h>

FpsCounter::FPS FpsCounter::GetFPS() noexcept
{
    UpdateFPS();

    return m_LastFps;
}

void FpsCounter::UpdateFPS() noexcept
{
    const Time currentTime = static_cast<Time>(glfwGetTime());

    ++m_Counter;

    if (currentTime - m_LastUpdateTime >= 1.0f)
    {
        UpdateTime(currentTime);

        m_Counter = Counter{};
    }
}


void FpsCounter::UpdateTime(const Time calcualtedTime) noexcept
{
        m_LastFps = static_cast<FPS>(m_Counter) / 
            (calcualtedTime - m_LastUpdateTime);

        m_LastUpdateTime = calcualtedTime;
}
