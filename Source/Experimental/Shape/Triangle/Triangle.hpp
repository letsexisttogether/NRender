#pragma once

#include "Experimental/Shape/Shape.hpp"

class Triangle : public Shape
{
public:
    Triangle() = delete;
    Triangle(const Triangle&) = delete;
    Triangle(Triangle&&) = default;

    Triangle(const GML::Vec2f a, const GML::Vec2f b, const GML::Vec2f c);

    ~Triangle() = default;

    Triangle& operator = (const Triangle&) = delete;
    Triangle& operator = (Triangle&&) = delete;
};
