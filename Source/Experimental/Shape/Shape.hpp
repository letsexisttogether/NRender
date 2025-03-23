#pragma once

#include <GML/Vector/Definitions.hpp>
#include <vector>

class Shape
{
public:
    using Vertices = std::vector<GML::Vec2f>; 
    using Indices = std::vector<std::int32_t>;

public:
    Shape() = default;
    Shape(const Shape&) = delete;
    Shape(Shape&&) = default;

    virtual ~Shape() = default;

    Vertices& GetVertices() noexcept;
    const Vertices& GetVertices() const noexcept;

    Indices& GetIndices() noexcept;
    const Indices& GetIndices() const noexcept;

    Shape& operator = (const Shape&) = delete;
    Shape& operator = (Shape&&) = delete;

protected:
    Vertices m_Vertices{};
    Indices m_Indices{};
};
