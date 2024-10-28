#include "Sprite.hpp"

#include <cassert>
#include <numeric>

#include "Basic/AttributePointer/AttributePointer.hpp"
#include "Basic/Buffer/VertexBuffer.hpp"
#include "Basic/Buffer/IndexBuffer.hpp"

NRenderSpaceStart

Sprite::Sprite(Shape&& shape, Shape&& textureBounds, const ID textureID,
    const ID shaderID)
    : m_TextureID{ textureID }, m_ShaderID{ shaderID }
{
    const Vertex2DBuffer::Count count = CreateVBO(std::move(shape),
        std::move(textureBounds));

    CreateEBO(count);
    CreateAttributes(count);
}

VertexArray& Sprite::GetVAO() noexcept
{
    return m_VAO;
}

ID Sprite::GetTextureID() const noexcept
{
    return m_TextureID;
}

ID Sprite::GetShaderID() const noexcept
{
    return m_ShaderID;
}


Vertex2DBuffer::Count Sprite::CreateVBO(Shape&& shape, Shape&& textureBounds)
    noexcept
{
    const auto vertices = shape.GetVertices();
    const auto uvCoords = textureBounds.GetVertices();

    const Vertex2DBuffer::Count verticesCount = vertices.size();

    assert(verticesCount == uvCoords.size() && "Vtx and UV not match");

    Vertex2DBuffer buffer{ verticesCount, GL_STATIC_DRAW }; 
    Vertex2DBuffer::ModernStorage data(verticesCount);

    for (Vertex2DBuffer::Count i = 0; i < verticesCount; ++i)
    {
        data.push_back(vertices[i]);
        data.push_back(uvCoords[i]);
    }

    buffer.UpdateData(data, 0);

    return verticesCount;
}

void Sprite::CreateEBO(const Vertex2DBuffer::Count count) noexcept
{
    IndexBuffer buffer{ count, GL_STATIC_DRAW }; 
    IndexBuffer::ModernStorage data(count);

    std::iota(data.begin(), data.end(), 0); 

    buffer.UpdateData(data, 0);
}

void Sprite::CreateAttributes(const Vertex2DBuffer::Count count) noexcept
{
    AttributePointer firstPointer{ 0, 2, GL_FALSE, count, 0 };
    AttributePointer secondPointer{ 1, 2, GL_FALSE, count, 2 };
}

NRenderSpaceEnd
