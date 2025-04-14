#pragma once

#include <GML/Vector/Definitions.hpp>
#include <array>
#include <cstddef>

#include "Utility/Convert/GetGLType.hpp"
#include "Vertex/VertexLayout.hpp"
#include "VAP/VertexAttribPointer.hpp"

struct ColorVertex
{
    GML::Vec2f Position{};
    GML::Vec3f Color{};
    GML::Vec2f UV{};
};

template <>
struct VertexLayout<ColorVertex>
{
    static auto SpawnAttributes(std::uint32_t startPosition = 0)
    {
        return std::array<VertexAttribPointer, 3>
        {
            VertexAttribPointer
            {
                startPosition, 2, GetGLType<GML::Vec2f>(),
                false, sizeof(ColorVertex), offsetof(ColorVertex, Position)
            },
            VertexAttribPointer
            {
                ++startPosition, 3, GetGLType<GML::Vec3f>(),
                false, sizeof(ColorVertex), offsetof(ColorVertex, Color)
            },
            VertexAttribPointer
            {
                ++startPosition, 2, GetGLType<GML::Vec2f>(),
                false, sizeof(ColorVertex), offsetof(ColorVertex, UV)
            },
        };
    }
};
