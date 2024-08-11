#include "Rectangle.hpp"

Rectangle::Rectangle(const Size width, const Size height)
    : m_Width{ width }, m_Height{ height }
{}

Rectangle::Rectangle(const Position origin, const Size width,
    const Size height)
    : m_Origin{ origin }, m_Width{ width }, m_Height{ height }
{}

Rectangle::Position Rectangle::GetOrigin() const noexcept
{
    return m_Origin;
}

void Rectangle::SetOrigin(const Position positon) noexcept
{
    m_Origin = positon;
}

Rectangle::Size Rectangle::GetWidth() const noexcept
{
    return m_Width;
}

Rectangle::Size Rectangle::GetHeight() const noexcept
{
    return m_Height;
}

Rectangle::Boundries Rectangle::CalculateBoundries() const noexcept
{
    const Vec2f leftBottom{ GetLeftBottom() };
    const Vec2f rightTop{ GetRightTop() };

    Boundries boundries 
    {
        { leftBottom.X(), rightTop.Y()   }, { 0.0f, 1.0f },
        { leftBottom.X(), leftBottom.Y() }, { 0.0f, 0.0f },
        { rightTop.X(),   rightTop.Y()   }, { 1.0f, 1.0f },
        { rightTop.X(),   leftBottom.Y() }, { 1.0f, 0.0f },
    };

    return boundries;
}


Vec2f Rectangle::GetLeftBottom() const noexcept
{
    const Size halfWidth = m_Width / 2.0f;
    const Size halfHeight = m_Height / 2.0f;

    const Vec2f leftBottom
    { 
        m_Origin.X() - halfWidth, 
        m_Origin.Y() - halfHeight 
    }; 
    
    return leftBottom;
}

Vec2f Rectangle::GetRightTop() const noexcept
{
    const Size halfWidth = m_Width / 2.0f;
    const Size halfHeight = m_Height / 2.0f;

    const Vec2f rightTop
    { 
        m_Origin.X() + halfWidth, 
        m_Origin.Y() + halfHeight 
    };

    return rightTop;
}
