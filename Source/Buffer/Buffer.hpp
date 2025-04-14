#pragma once

#include <cassert>
#include <vector>

#include "Core/Core.hpp"
#include "Boundable/Boundable.hpp"

template <GLenum _BufferType>
class Buffer : protected Boundable
{
public:
    Buffer() = delete;

    Buffer(const Buffer&) = delete;
    Buffer(Buffer&&) = default;

    explicit Buffer(const bool shouldBind);

    ~Buffer();

    void Bind() noexcept override;
    void Unbind() noexcept override;

    template <typename _Type>
    void SetData(const std::vector<_Type>& data, const GLenum dataHint)
        noexcept;

    template <typename _Type>
    void SetSubData(const std::vector<_Type>& data, const std::size_t offset)
        noexcept;

    template <typename _Type>
    void SetSubData(const _Type& data, const std::size_t offset) noexcept;

    GLenum GetBufferType() const noexcept;

    Buffer& operator = (const Buffer&) = delete;
    Buffer& operator = (Buffer&&) = delete;

protected:
    void Generate() noexcept override;

private:
    std::size_t m_BufferSize{};
};


template <GLenum _BufferType>
template <typename _Type>
void Buffer<_BufferType>::SetData(const std::vector<_Type>& data,
    const GLenum dataHint) noexcept
{
    m_BufferSize = data.size() * sizeof(_Type);

    glBufferData(_BufferType, m_BufferSize, data.data(), dataHint);
}

template <GLenum _BufferType>
template <typename _Type>
void Buffer<_BufferType>::SetSubData(const std::vector<_Type>& data,
    const std::size_t offset) noexcept
{
    const std::size_t dataSize = data.size() * sizeof(_Type);

    // TODO: Change to Application::CauseError() or something like that
    assert(m_BufferSize >= offset + dataSize 
        && "SetSubData: Out of bounds write attempt!");

    glBufferSubData(_BufferType, offset, dataSize, data.data());
}

template <GLenum _BufferType>
template <typename _Type>
void Buffer<_BufferType>::SetSubData(const _Type& data, const std::size_t offset)
    noexcept
{
    const std::size_t dataSize = sizeof(_Type);

    // TODO: Change to Application::CauseError() or something like that
    assert(m_BufferSize >= offset + dataSize 
        && "SetSubData: Out of bounds write attempt!");

    glBufferSubData(_BufferType, offset, dataSize, &data);
}

using VertexBufferObject = Buffer<GL_ARRAY_BUFFER>;
using ElementBufferObject = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
