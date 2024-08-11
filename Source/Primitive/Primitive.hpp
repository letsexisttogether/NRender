#pragma once

#include <GML/Vector/Definitions.hpp>

#include "AttributePointer/AttributePointer.hpp"
#include "Drawable/Drawable.hpp"
#include "Buffer/VertexBuffer.hpp"
#include "Buffer/IndexBuffer.hpp"
#include "VertexArray/VertexArray.hpp"

// Build out of triangles
class Primitive : public Drawable
{
protected:
    using Attributes = std::vector<AttributePointer>;

public:
    Primitive() = default;
    Primitive(const Primitive&) = delete;
    Primitive(Primitive&&) = default;

    virtual ~Primitive() = default;

    void Draw() noexcept override;

    Primitive& operator = (const Primitive&) noexcept = delete;
    Primitive& operator = (Primitive&&) noexcept = default;

protected:
    virtual void Generate() noexcept = 0;

    void SetVertices(Vertex2DBuffer&& vertices) noexcept;
    void SetIndices(IndexBuffer&& indices) noexcept;

private:
    VertexArray m_VAO{};

    Vertex2DBuffer m_Vertices{};
    IndexBuffer m_Indices{};

protected:
    Attributes m_Attributes{};
};
