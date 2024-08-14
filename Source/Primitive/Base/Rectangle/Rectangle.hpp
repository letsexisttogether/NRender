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

    Rectangle(const Size width, const Size height);
    Rectangle(const Position origin, const Size width, const Size height);

    ~Rectangle() = default;

    Position GetOrigin() const noexcept;
    void SetOrigin(const Position positon) noexcept;

    Size GetWidth() const noexcept;
    Size GetHeight() const noexcept;

    bool CheckPointColision(const GML::Vec2f point) const noexcept;

    Rectangle& operator = (const Rectangle&) noexcept = default;
    Rectangle& operator = (Rectangle&&) noexcept = default;

protected:
    Boundries CalculateBoundries() const noexcept;

    GML::Vec2f GetLeftBottom() const noexcept;
    GML::Vec2f GetRightTop() const noexcept;

protected:
    Position m_Origin{};
    Size m_Width{};
    Size m_Height{};
};
