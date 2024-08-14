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

    virtual void Bind() noexcept = 0;
    virtual void UnBind() noexcept = 0;

    BoundableID GetID() const noexcept;

    Boundable& operator = (const Boundable&) noexcept = delete;
    Boundable& operator = (Boundable&& boundable) noexcept; 

protected:
    virtual void Generate() noexcept = 0;

protected:
    BoundableID m_ID{}; 
    Type m_Type{};
};
