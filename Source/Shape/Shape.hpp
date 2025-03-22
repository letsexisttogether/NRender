#pragma once

#include "Utility/Naming.hpp"
#include "Basic/Buffer/VertexBuffer.hpp"
#include <optional>

NRenderSpaceStart

class Shape
{
public:
    using Vertices = std::vector<Vertex>;

public:
    Shape() = default;

    virtual ~Shape() = default;

    Vertex2DBuffer GetVBO() noexcept;
    // std::optional<EBO> GetEBO() noexcept;

protected:
};

NRenderSpaceEnd
