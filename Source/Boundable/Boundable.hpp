#pragma once

#include <cstdint>

class Boundable
{
public:
    using BoundableID = std::uint32_t;
    using Type = std::uint32_t;

public:
    Boundable() = delete;
    Boundable(const Boundable&) = default;
    Boundable(Boundable&&) = default;

    Boundable(const Type type);

    virtual ~Boundable() = default;

    virtual void Bind() noexcept;
    virtual void UnBind() noexcept;

    BoundableID GetID() const noexcept;

    Boundable& operator = (const Boundable&) noexcept = default;
    Boundable& operator = (Boundable&&) noexcept = default;

protected:
    BoundableID m_ID{}; 
    Type m_Type{};
};
