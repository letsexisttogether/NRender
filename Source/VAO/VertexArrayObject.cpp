#include "VertexArrayObject.hpp"

#include "Core/Core.hpp"

VertexArrayObject::VertexArrayObject(const bool shouldBind)
{
    Init(shouldBind);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArrayObject::Bind() noexcept
{
    glBindVertexArray(m_ID);
}

void VertexArrayObject::Unbind() noexcept
{
    glBindVertexArray(0); 
}

void VertexArrayObject::Generate() noexcept
{
    glGenVertexArrays(1, &m_ID);
}
