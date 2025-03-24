#pragma once

#include <vector>

#include "Core/Core.hpp"
#include "Experimental/Boundable/Boundable.hpp"

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

    GLenum GetBufferType() const noexcept;

    Buffer& operator = (const Buffer&) = delete;
    Buffer& operator = (Buffer&&) = delete;

protected:
    void Generate() noexcept override;
};

template <GLenum _BufferType>
template <typename _Type>
void Buffer<_BufferType>::SetData(const std::vector<_Type>& data,
    const GLenum dataHint) noexcept
{
    glBufferData(_BufferType, data.size() * sizeof(_Type),
        data.data(), dataHint);
}


using VertexBufferObject = Buffer<GL_ARRAY_BUFFER>;
using ElementBufferObject = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
