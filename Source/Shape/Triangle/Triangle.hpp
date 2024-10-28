#pragma once

#include "Shape/Shape.hpp"

NRenderSpaceStart

class Triangle : public Shape
{
public:
    Triangle() = delete;

    Triangle(const Vertex& a, const Vertex& b, const Vertex& c);

    ~Triangle() = default;
};

NRenderSpaceEnd
