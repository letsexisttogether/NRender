#include "IDable.hpp"

IDable::IDable(const ID id)
    : m_ID{ id }
{}

IDable::ID IDable::GetID() const noexcept
{
    return m_ID;
}

void IDable::SetID(const ID id) noexcept
{
    m_ID = id;
}

bool IDable::operator == (const IDable& idadble) const noexcept
{
    return (m_ID == idadble.m_ID);
}
