#include "VertexBufferObject.hpp"

#include "Render/Render.hpp"

VertexBufferObject::VertexBufferObject(const bool shouldBind)
{
    Init(shouldBind);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &m_ID);
}

void VertexBufferObject::Bind() noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBufferObject::Unbind() noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Generate() noexcept
{
    glGenBuffers(1, &m_ID);
}
