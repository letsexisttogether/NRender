#pragma once

#include <cstddef>

#include "Render/Render.hpp"
#include "Experimental/Boundable/Boundable.hpp"

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
        const bool m_ShouldNormalize, const Size stride,
        const Size previousSize);

    ~VertexAttribPointer() = default;

    void Bind() noexcept override;
    void Unbind() noexcept override;

    // TODO: Think whether this method should be const-specified
    VertexAttribPointer SpawnNext(const Size size) noexcept;

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
    const GLenum type, const bool m_ShouldNormalize,
    const Size stride, const Size previousSize)
    : m_Size{ size }, m_Type{ type }, m_ShouldNormalize{ m_ShouldNormalize },
    m_Stride{ stride }, 
    m_Offset{ reinterpret_cast<void*>(previousSize * sizeof(_DataType)) }
{
    m_ID = location;

    Init(true);
}

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
VertexAttribPointer<_DataType> VertexAttribPointer<_DataType>::
    SpawnNext(const Size size) noexcept
{
    VertexAttribPointer vap
    {
        m_ID + 1, size, m_Type, m_ShouldNormalize,
        m_Stride, m_Size
    };

    return vap;
}

template <typename _DataType>
void VertexAttribPointer<_DataType>::Generate() noexcept
{
    glVertexAttribPointer(m_ID, m_Size, m_Type, m_ShouldNormalize,
        m_Stride * sizeof(_DataType), m_Offset);
}
