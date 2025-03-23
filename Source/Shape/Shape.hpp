#pragma once

// NRenderSpaceStart

class Shape
{
public:
    using Vertices = std::vector<Vertex>;

public:
    Shape() = default;

    virtual ~Shape() = default;


    // std::optional<EBO> GetEBO() noexcept;

protected:
};

// NRenderSpaceEnd
