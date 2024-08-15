#include "Chunk.hpp"

Chunk::Chunk(const IDable idable, const Rectangle& rectangle)
    : IDable{ idable }, Rectangle{ rectangle }
{}

void Chunk::AddObject(const IDable::ID id) noexcept
{
    m_Objects.insert(id);    
}

void Chunk::RemoveObject(const IDable::ID id) noexcept
{
    m_Objects.erase(id);
}

std::size_t Chunk::Hash::operator () (const Chunk& chunk)
    const noexcept
{
    return chunk.GetID();
}

 bool Chunk::Equal::operator () (const Chunk& first, const Chunk& second)
    const noexcept
{
    return first.IDable::operator == (second);
}
