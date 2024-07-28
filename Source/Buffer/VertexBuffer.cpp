#include "VertexBuffer.hpp"

#include "GLEW/glew.h"

VertexBuffer::VertexBuffer(Data&& data)
    : Boundable{ GL_ARRAY_BUFFER }, m_Data{ std::move(data) }
{}

void VertexBuffer::FillData() noexcept
{
    glBufferData(m_Type, m_Data.size() * sizeof(DataType),
        m_Data.data(), GL_STATIC_DRAW);
}

VertexBuffer::DataCount VertexBuffer::GetCount() const noexcept
{
    return m_Data.size();
}

