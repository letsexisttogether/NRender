#include "IDable.hpp"
#include <functional>

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

    
std::size_t IDable::Hash::operator () (const IDable& idable)
    const noexcept
{
    return idable.m_ID;
}

bool IDable::Equal::operator () (const IDable& first, const IDable& second)
        const noexcept
{
    return (first == second);
}

