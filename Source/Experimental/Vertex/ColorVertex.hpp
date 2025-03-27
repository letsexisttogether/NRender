#pragma once

#include <GML/Vector/Definitions.hpp>
#include <array>
#include <cstddef>

#include "Experimental/Utility/Convert/GetGLType.hpp"
#include "Experimental/Vertex/VertexStructure.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"

struct ColorVertex
{
    GML::Vec2f Position{};
    GML::Vec3f Color{};
};

template <>
struct VertexLayout<ColorVertex>
{
    static auto SpawnAttributes()
    {
        return std::array<VertexAttribPointer, 2>
        {
            VertexAttribPointer
            {
                0, 2, GetGLType<GML::Vec2f>(),
                false, sizeof(ColorVertex), 0
            },
            VertexAttribPointer
            {
                1, 3, GetGLType<GML::Vec3f>(),
                false, sizeof(ColorVertex), offsetof(ColorVertex, Color)
            }
        };
    }
};
