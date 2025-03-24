#pragma once

#include "Experimental/Vertex/Vertex.hpp"

struct ColoredVertex : public Vertex
{
    GML::Vec3f Color{};
};
