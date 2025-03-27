#pragma once

#include <GML/Vector/Definitions.hpp>
#include <array>
#include <cstddef>

#include "Experimental/Utility/Convert/GetGLType.hpp"
#include "Experimental/Vertex/VertexStructure.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"

struct ComplexVertex 
{
    GML::Vec2f Position{};
    float Scale{};
};

template <>
struct VertexLayout<ComplexVertex>
{
    static auto SpawnAttributes(const std::uint32_t startPosition = 0)
    {
        return std::array<VertexAttribPointer, 2>
        {
            VertexAttribPointer
            {
                startPosition, 2, GetGLType<GML::Vec2f>(),
                false, sizeof(ComplexVertex), offsetof(ComplexVertex, Position)
            },
            VertexAttribPointer
            {
                startPosition + 1, 1, GetGLType<float>(),
                false, sizeof(ComplexVertex), offsetof(ComplexVertex, Scale)
            }
        };
    }
};
