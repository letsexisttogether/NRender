#pragma once

#include <unordered_set>

#include "Front/Drawable/Drawable.hpp"
#include "Front/IDGenerator/IDGenerator.hpp"
#include "Front/Primitive/Base/Rectangle/Rectangle.hpp"

class Chunk : public Rectangle, public Drawable
{
public:
    using Objects = std::unordered_set<IDGenerator::ID>;

public:
    Chunk() = delete;
    Chunk(const Chunk&) = default;
    Chunk(Chunk&&) = default;

    Chunk(const Rectangle& rectangle);

    ~Chunk() = default;

    void AddObject(const IDGenerator::ID id) noexcept;
    void RemoveObject(const IDGenerator::ID id) noexcept;

    void Draw() noexcept override;
    
    Chunk& operator = (const Chunk&) noexcept;
    Chunk& operator = (Chunk&&) noexcept;

private:
    Objects m_Objects{}; 
};
