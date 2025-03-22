#include "Boundable.hpp"

#include <algorithm>

Boundable::Boundable(Boundable&& boundable)
{
    std::swap(m_ID, boundable.m_ID);
}

void Boundable::Init(const bool shouldBind) noexcept
{
    Generate();

    if (shouldBind)
    {
        Bind();
    }
}

std::int32_t Boundable::GetID() const noexcept
{
    return m_ID;
}
