#pragma once

#include <vector>

#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/Vertex/VertexLayout.hpp"

template <class _Vertex>
class Sprite
{
public:
    Sprite() = delete;
    Sprite(const Sprite&) = delete;
    Sprite(Sprite&&) = default;

    Sprite(const std::vector<_Vertex>& data);

    ~Sprite() = default; 

    VertexArrayObject& GetVAO() noexcept;

    std::size_t GetSize() noexcept;

    Sprite& operator = (const Sprite&) = delete;
    Sprite& operator = (Sprite&&) = delete;

private:
    VertexArrayObject m_VAO;
    std::size_t m_VerticesSize;
};


template <class _Vertex>
Sprite<_Vertex>::Sprite(const std::vector<_Vertex>& data)
    : m_VAO{ true }, m_VerticesSize{ data.size() }
{
    VertexBufferObject VBO{ true };
    VBO.SetData(data, GL_STATIC_DRAW);

    VertexLayout<_Vertex>::SpawnAttributes();

    m_VAO.Unbind();
}

template <class _Vertex>
VertexArrayObject& Sprite<_Vertex>::GetVAO() noexcept
{
    return m_VAO;
}

template <class _Vertex>
std::size_t Sprite<_Vertex>::GetSize() noexcept
{
    return m_VerticesSize;
}
