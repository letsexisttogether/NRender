#pragma once

#include <cstdint>

class IDGenerator
{
public:
    using ID = std::uint32_t; 

public:    
    IDGenerator() = default;
    IDGenerator(const IDGenerator&) = default;
    IDGenerator(IDGenerator&&) = default;

    IDGenerator(const ID startValue);

    ~IDGenerator() = default;

    ID GetNext() noexcept;

    IDGenerator& operator = (const IDGenerator&) noexcept = default;
    IDGenerator& operator = (IDGenerator&&) noexcept = default;

private:
    ID m_CurrentID{};
};
