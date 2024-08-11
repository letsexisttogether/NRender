#include "Primitive.hpp"

#include <GLEW/glew.h>

void Primitive::Draw() noexcept
{
    m_VAO.Bind();

    glDrawElements(GL_TRIANGLES, m_Indices.GetCount(), GL_UNSIGNED_INT, 0);
}

void Primitive::SetVertices(Vertex2DBuffer&& vertices) noexcept
{
    m_Vertices = std::move(vertices);
}

void Primitive::SetIndices(IndexBuffer&& indices) noexcept
{
    m_Indices = std::move(indices);
}
