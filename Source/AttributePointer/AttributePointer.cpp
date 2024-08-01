#include "AttributePointer.hpp"

#include "Buffer/VertexBuffer.hpp"
#include "GLEW/glew.h"

AttributePointer::AttributePointer(const BoundableID id, const Count count,
    const IsNormalized isNormalizzed, const Stride stride, const Offset offset)
    : Boundable{ GL_FLOAT }, m_Count{ count }, m_IsNormalized{ isNormalizzed }, 
    m_Stride{ stride }, m_Offset{ offset }
{
    m_ID = id;

    Generate();
}

AttributePointer::~AttributePointer()
{
    UnBind();
}

void AttributePointer::Bind() noexcept
{
    glEnableVertexAttribArray(m_ID);
}

void AttributePointer::UnBind() noexcept
{
    glDisableVertexAttribArray(m_ID);
}

void AttributePointer::Generate() noexcept
{
    glVertexAttribPointer(m_ID, m_Count, m_Type, m_IsNormalized,
        m_Stride * sizeof(VertexType), (void*)(m_Offset * sizeof(VertexType)));
}
