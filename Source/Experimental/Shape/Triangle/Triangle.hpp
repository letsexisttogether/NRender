#pragma once

#include "Experimental/Shape/Shape.hpp"
#include "Experimental/Vertex/ColoredVertex.hpp"

class Triangle : public Shape
{
public:
    Triangle() = delete;
    Triangle(const Triangle&) = delete;
    Triangle(Triangle&&) = default;

    Triangle(const Vertex a, const Vertex b, const Vertex c);

    Triangle(const ColoredVertex a, const ColoredVertex b,
        const ColoredVertex c);

    ~Triangle() = default;

    Triangle& operator = (const Triangle&) = delete;
    Triangle& operator = (Triangle&&) = delete;
};
