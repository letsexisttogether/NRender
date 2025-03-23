#include "Rectangle.hpp"

Rectangle::Rectangle(const GML::Vec2f a, const GML::Vec2f b,
    const GML::Vec2f c, const GML::Vec2f d)
{
    m_Vertices = { a, b, c, d };

    m_Indices = { 0, 1, 3, 1, 2, 3 };
}
