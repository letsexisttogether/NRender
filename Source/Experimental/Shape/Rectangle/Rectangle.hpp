#pragma once

#include "Experimental/Shape/Shape.hpp"

class Rectangle : public Shape
{
public:
    Rectangle() = delete;
    Rectangle(const Rectangle&) = delete;
    Rectangle(Rectangle&&) = default;

    Rectangle(const GML::Vec2f a, const GML::Vec2f b,
        const GML::Vec2f c, const GML::Vec2f d);

    ~Rectangle() = default;

    Rectangle& operator = (const Rectangle&) = delete;
    Rectangle& operator = (Rectangle&&) = delete;
};
