#include "Shape.hpp"

Shape::Vertices& Shape::GetVertices() noexcept
{
    return m_Vertices;
}

const Shape::Vertices& Shape::GetVertices() const noexcept
{
    return m_Vertices;
}

Shape::Indices& Shape::GetIndices() noexcept
{
    return m_Indices;
}

const Shape::Indices& Shape::GetIndices() const noexcept
{
    return m_Indices;
}
