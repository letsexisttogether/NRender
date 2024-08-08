#include "VertexArray.hpp"

#include "GLEW/glew.h"

VertexArray::VertexArray(const bool shouldPrepare) 
{
    Generate();

    if (shouldPrepare)
    {
        Bind();
    }
}

VertexArray::~VertexArray()
{
    UnBind();

    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() noexcept
{
    glBindVertexArray(m_ID);
}

void VertexArray::UnBind() noexcept
{
    glBindVertexArray(0);
}

void VertexArray::Generate() noexcept
{
    glGenVertexArrays(1, &m_ID); 
}
