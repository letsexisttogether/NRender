#pragma once

#include <cstddef>
#include <cstdint>

class IDable
{
public:
    using ID = std::uint32_t;

public:
    IDable() = default;
    IDable(const IDable&) = default;
    IDable(IDable&&) = default;

    IDable(const ID id);

    ~IDable() = default;

    ID GetID() const noexcept;
    void SetID(const ID id) noexcept;

    bool operator == (const IDable& idadble) const noexcept;

    IDable& operator = (const IDable&) = default;
    IDable& operator = (IDable&&) = default;

public:
    struct Hash
    {
        std::size_t operator () (const IDable& idable) const noexcept;
    };

    struct Equal 
    {
        bool operator () (const IDable& first, const IDable& second)
            const noexcept;
    };

private:
    ID m_ID{};    
};
