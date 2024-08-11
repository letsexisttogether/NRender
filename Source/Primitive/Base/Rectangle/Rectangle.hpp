#pragma once

#include <GML/Vector/Definitions.hpp>

#include "Buffer/VertexBuffer.hpp"

class Rectangle
{
public:
    using Size = float;
    using Position = Vec2f;

    using Boundries = Vertex2DBuffer::Data;

public:
    Rectangle() = default;
    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;

    Rectangle(const Size width, const Size height);
    Rectangle(const Position origin, const Size width, const Size height);

    ~Rectangle() = default;

    Position GetOrigin() const noexcept;
    void SetOrigin(const Position positon) noexcept;

    Size GetWidth() const noexcept;
    Size GetHeight() const noexcept;

    Rectangle& operator = (const Rectangle&) noexcept = default;
    Rectangle& operator = (Rectangle&&) noexcept = default;

protected:
    Boundries CalculateBoundries() const noexcept;

    Vec2f GetLeftBottom() const noexcept;
    Vec2f GetRightTop() const noexcept;

protected:
    Position m_Origin{};
    Size m_Width{};
    Size m_Height{};
};
