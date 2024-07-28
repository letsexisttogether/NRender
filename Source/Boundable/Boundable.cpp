#include "Boundable.hpp"

#include "GLEW/glew.h"

Boundable::Boundable(const Type type)
    : m_Type{ type }
{
    glGenBuffers(1, &m_ID);
}


void Boundable::Bind() noexcept
{
    glBindBuffer(m_Type, m_ID);
}

void Boundable::UnBind() noexcept
{
    glBindBuffer(m_Type, 0);
}

Boundable::BoundableID Boundable::GetID() const noexcept
{
    return m_ID;
}
