#pragma once

#include <cstdint>

class Boundable
{
public:
    using BoundableID = std::uint32_t;
    using Type = std::uint32_t;

public:
    Boundable() = default;
    Boundable(const Boundable&) = default;
    Boundable(Boundable&&) = default;

    Boundable(const Type type);

    virtual ~Boundable();

    virtual void Bind() noexcept;
    virtual void UnBind() noexcept;

    BoundableID GetID() const noexcept;

    Boundable& operator = (const Boundable&) noexcept = default;
    Boundable& operator = (Boundable&&) noexcept = default;

protected:
    virtual void Generate() noexcept;

protected:
    BoundableID m_ID{}; 
    Type m_Type{};
};
