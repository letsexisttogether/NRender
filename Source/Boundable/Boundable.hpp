#pragma once

#include <cstdint>

class Boundable
{
public:
    using BoundableID = std::uint32_t;
    using Type = std::uint32_t;

public:
    Boundable() = default;
    Boundable(const Boundable&) = delete;
    Boundable(Boundable&& boundable);

    Boundable(const Type type);

    virtual ~Boundable() = default;

    virtual void Bind() noexcept;
    virtual void UnBind() noexcept;

    BoundableID GetID() const noexcept;

    Boundable& operator = (const Boundable&) noexcept = delete;
    Boundable& operator = (Boundable&& boundable) noexcept; 

protected:
    virtual void Generate() noexcept;

protected:
    BoundableID m_ID{}; 
    Type m_Type{};
};
