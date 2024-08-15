#pragma once

#include <set>

#include "Front/IDable/IDable.hpp"
#include "Front/Primitive/Base/Rectangle/Rectangle.hpp"

class Chunk : public IDable, public Rectangle 
{
public:
    using Objects = std::multiset<IDable::ID>;

public:
    Chunk() = delete;
    Chunk(const Chunk&) = default;
    Chunk(Chunk&&) = default;

    Chunk(const IDable idable, const Rectangle& rectangle);

    ~Chunk() = default;

    void AddObject(const IDable::ID id) noexcept;
    void RemoveObject(const IDable::ID id) noexcept;
    
    Chunk& operator = (const Chunk&) noexcept;
    Chunk& operator = (Chunk&&) noexcept;

public:
    struct Hash
    {
        std::size_t operator () (const Chunk& chunk) const noexcept;
    };

    struct Equal 
    {
         bool operator () (const Chunk& first, const Chunk& second)
             const noexcept;
    };

private:
    Objects m_Objects{}; 
};
