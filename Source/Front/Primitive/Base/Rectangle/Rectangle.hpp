#pragma once

#include <vector>
#include <GML/Vector/Definitions.hpp>

class Rectangle
{
public:
    using Size = float;
    using Position = GML::Vec2f;

    using Boundries = std::vector<GML::Vec2f>;

public:
    Rectangle() = default;
    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;

    Rectangle(const Position leftBottom, const Position rightTop);

    virtual ~Rectangle() = default;

    Position GetOrigin() const noexcept;

    Position GetLeftBotton() const noexcept;
    Position GetRightTop() const noexcept;

    Rectangle& operator = (const Rectangle&) noexcept = default;
    Rectangle& operator = (Rectangle&&) noexcept = default;

protected:
    Position m_LeftBottom{};
    Position m_RightTop{};
};
