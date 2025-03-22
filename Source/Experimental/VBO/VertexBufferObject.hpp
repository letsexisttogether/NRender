#pragma once

#include <cstdint>

#include "Experimental/Boundable/Boundable.hpp"

class VertexBufferObject : protected Boundable
{
public:
    VertexBufferObject() = delete;
    VertexBufferObject(const VertexBufferObject&) = delete;
    VertexBufferObject(VertexBufferObject&&) = default;

    explicit VertexBufferObject(const bool shouldBind);

    ~VertexBufferObject();

    void Bind() noexcept override;
    void Unbind() noexcept override;

    VertexBufferObject& operator = (const VertexBufferObject&) = delete;
    VertexBufferObject& operator = (VertexBufferObject&&) = delete;

protected:
    void Generate() noexcept override;
};
