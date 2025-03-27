#pragma once

#include <cstddef>

#include "Core/Core.hpp"
#include "Experimental/Boundable/Boundable.hpp"
#include "Experimental/Utility/Convert/GetGLType.hpp"

// TODO: Remove the template. Remove the GetGLenum constructor
template <typename _DataType>
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

    VertexAttribPointer(const std::uint32_t location,
        const Size size, const bool shouldNormalize,
        const Size stride, const Size offset);

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


template <typename _DataType>
VertexAttribPointer<_DataType>::VertexAttribPointer
    (const std::uint32_t location, const Size size,
    const GLenum type, const bool shouldNormalize,
    const Size stride, const Size offset)
    : m_Size{ size }, m_Type{ type },
    m_ShouldNormalize{ shouldNormalize }, m_Stride{ stride },
    m_Offset{ reinterpret_cast<void*>(offset) }
{
    m_ID = location;

    Init(true);
}

template <typename _DataType>
VertexAttribPointer<_DataType>::VertexAttribPointer
    (const std::uint32_t location, const Size size,
    const bool shouldNormalize, const Size stride, const Size offset)
    : VertexAttribPointer{ location, size, GetGLType<_DataType>(),
        shouldNormalize, stride, offset }
{}

template <typename _DataType>
void VertexAttribPointer<_DataType>::Bind() noexcept
{
    glEnableVertexAttribArray(m_ID);
}

template <typename _DataType>
void VertexAttribPointer<_DataType>::Unbind() noexcept
{
    glDisableVertexAttribArray(m_ID);
}

template <typename _DataType>
void VertexAttribPointer<_DataType>::SetDivisor(const Size divisor) noexcept
{
    glVertexAttribDivisor(m_ID, divisor);
}

template <typename _DataType>
void VertexAttribPointer<_DataType>::Generate() noexcept
{
    glVertexAttribPointer(m_ID, m_Size, m_Type, m_ShouldNormalize,
        m_Stride, m_Offset);
}
