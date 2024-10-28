#pragma once

#include "Utility/Naming.hpp"
#include "Basic/VertexArray/VertexArray.hpp"

NRenderSpaceStart

class Shape
{
public:
    using Vertices = std::vector<Vertex>;

public:
    Shape() = default;

    virtual ~Shape() = default;

    Vertices GetVertices() noexcept;

protected:
    Vertices m_Vertices{};
};

NRenderSpaceEnd
