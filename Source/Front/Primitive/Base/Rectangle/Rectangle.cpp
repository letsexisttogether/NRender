#include "Rectangle.hpp"

Rectangle::Rectangle(const Position leftBottom, const Position rightTop)
    : m_LeftBottom{ leftBottom }, m_RightTop{ rightTop }
{}

Rectangle::Position Rectangle::GetLeftBottom() const noexcept
{
    return m_LeftBottom;
}

Rectangle::Position Rectangle::GetRightTop() const noexcept
{
    return m_RightTop;
}
