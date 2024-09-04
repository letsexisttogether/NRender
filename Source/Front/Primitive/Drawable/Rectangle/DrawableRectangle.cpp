#include "DrawableRectangle.hpp"

#include "Basic/AttributePointer/AttributePointer.hpp"
#include "Basic/Buffer/VertexBuffer.hpp"

DrawableRectangle::DrawableRectangle(Rectangle&& coordinates,
    const Rectangle& textureCoords)
    : Rectangle{ std::move(coordinates) }
{
    const Position texLB{ textureCoords.GetLeftBottom() };
    const Position texRT{ textureCoords.GetRightTop() };

    const Vertex2DBuffer::ModernStorage vertices
    {
        { m_LeftBottom.X(), m_LeftBottom.Y() }, { texLB.X(), texLB.Y() },
        { m_LeftBottom.X(), m_RightTop.Y()   }, { texLB.X(), texRT.Y() },
        { m_RightTop.X(),   m_RightTop.Y()   }, { texRT.X(), texRT.Y() },
        { m_RightTop.X(),   m_LeftBottom.Y() }, { texRT.X(), texLB.Y() }
    };

    const IndexBuffer::ModernStorage indices
    {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    m_VBO.UpdateData(vertices, 0);
    m_EBO.UpdateData(indices, 0);

    AttributePointer firstPointer{ 0, 2, GL_FALSE, 4, 0 };
    AttributePointer secondPointer{ 1, 2, GL_FALSE, 4, 2 };

    m_VAO.UnBind();
}

void DrawableRectangle::Draw() noexcept
{
    m_VAO.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

