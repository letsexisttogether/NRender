#pragma once

#include "Experimental/Boundable/Boundable.hpp"

class VertexArrayObject : protected Boundable
{
public:
    VertexArrayObject() = delete;
    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject(VertexArrayObject&&) = default;

    explicit VertexArrayObject(const bool shouldBind);

    ~VertexArrayObject();

    void Bind() noexcept override;
    void Unbind() noexcept override;

    VertexArrayObject& operator = (const VertexArrayObject&) = delete;
    VertexArrayObject& operator = (VertexArrayObject&&) = delete;

protected:
    void Generate() noexcept override;
};
