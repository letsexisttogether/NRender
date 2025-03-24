#pragma once

#include "Experimental/Shape/Shape.hpp"
#include "Experimental/Vertex/ColoredVertex.hpp"

class Rectangle : public Shape
{
public:
    Rectangle() = delete;
    Rectangle(const Rectangle&) = delete;
    Rectangle(Rectangle&&) = default;

    Rectangle(const Vertex a, const Vertex b,
        const Vertex c, const Vertex d);

    Rectangle(const ColoredVertex a, const ColoredVertex b,
        const ColoredVertex c, const ColoredVertex  d);

    ~Rectangle() = default;

    Rectangle& operator = (const Rectangle&) = delete;
    Rectangle& operator = (Rectangle&&) = delete;
};
