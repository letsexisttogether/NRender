#include "IDGenerator.hpp"

IDGenerator::IDGenerator(const ID startValue)
    : m_CurrentID{ startValue }
{}

IDGenerator::ID IDGenerator::GetNext() noexcept
{
    return m_CurrentID++;
}
