#pragma once

#include <GML/Vector/Definitions.hpp>
#include <array>

#include "Utility/Convert/GetGLType.hpp"
#include "Vertex/VertexLayout.hpp"
#include "VAP/VertexAttribPointer.hpp"

struct Vertex
{
    GML::Vec2f Position{};
};

// TODO: Make this function constexpr
template <>
struct VertexLayout<Vertex>
{
    static auto SpawnAttributes(const uint32_t startPosition = 0)
    {
        return std::array<VertexAttribPointer, 1>
        {
            VertexAttribPointer
            {
                startPosition, 2, GetGLType<GML::Vec2f>(),
                false, sizeof(Vertex), 0
            }
        };
    }
};
