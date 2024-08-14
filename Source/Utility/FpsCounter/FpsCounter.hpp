#pragma once

#include <cstdint>

class FpsCounter
{
public:
    using FPS = float;

private:
    using Counter = std::uint16_t;
    using Time = float;

public:
    FpsCounter() = default;
    FpsCounter(const FpsCounter&) = delete;
    FpsCounter(FpsCounter&&) = delete;

    FPS GetFPS() noexcept;

    FpsCounter& operator = (const FpsCounter&) noexcept = delete;
    FpsCounter& operator = (FpsCounter&&) noexcept = delete;

private:
    void UpdateFPS() noexcept;

    void UpdateTime(const Time calcualtedTime) noexcept;

private:
    FPS m_LastFps{};

    Time m_LastUpdateTime{};
    Counter m_Counter{};
};
