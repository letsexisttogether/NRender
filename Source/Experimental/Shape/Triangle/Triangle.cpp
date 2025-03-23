#include "Triangle.hpp"

Triangle::Triangle(const GML::Vec2f a, const GML::Vec2f b,
    const GML::Vec2f c)
{
    m_Vertices = { a, b, c };

    m_Indices = { 0, 1, 2 };
}
