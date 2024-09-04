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
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() noexcept
{
    if (m_CurrentBoundID != m_ID)
    {
        glBindVertexArray(m_ID);

        m_CurrentBoundID = m_ID;
    }
}

void VertexArray::UnBind() noexcept
{
    m_CurrentBoundID = 0;

    glBindVertexArray(0);
}

void VertexArray::Generate() noexcept
{
    glGenVertexArrays(1, &m_ID); 
}
