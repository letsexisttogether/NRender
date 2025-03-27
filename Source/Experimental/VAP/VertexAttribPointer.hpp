#pragma once

#include <cstddef>

#include "Core/Core.hpp"
#include "Experimental/Boundable/Boundable.hpp"

class VertexAttribPointer : protected Boundable
{
public:
    using Size = std::size_t;

public:
    VertexAttribPointer() = delete;

    VertexAttribPointer(const VertexAttribPointer&) = delete;
    VertexAttribPointer(VertexAttribPointer&&) = default;

    VertexAttribPointer(const std::uint32_t location,
        const Size size, const GLenum type,
        const bool shouldNormalize, const Size stride,
        const Size offset);

    ~VertexAttribPointer() = default;

    void Bind() noexcept override;
    void Unbind() noexcept override;

    void SetDivisor(const Size divisor) noexcept;

    VertexAttribPointer& operator = (const VertexAttribPointer&) = delete;
    VertexAttribPointer& operator = (VertexAttribPointer&&) = delete;

protected:
    void Generate() noexcept override;

protected:
    Size m_Size{};
    GLenum m_Type{};
    bool m_ShouldNormalize{};
    Size m_Stride{};
    void* m_Offset{};
};
