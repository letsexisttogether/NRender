#include "Buffer.hpp"

template <GLenum _BufferType>
Buffer<_BufferType>::Buffer(const bool shouldBind)
{
    Init(shouldBind);
}

template <GLenum _BufferType>
Buffer<_BufferType>::~Buffer()
{
    glDeleteBuffers(1, &m_ID);
}

template <GLenum _BufferType>
void Buffer<_BufferType>::Bind() noexcept
{
    glBindBuffer(_BufferType, m_ID);
}

template <GLenum _BufferType>
void Buffer<_BufferType>::Unbind() noexcept
{
    glBindBuffer(_BufferType, 0);
}

template <GLenum _BufferType>
GLenum Buffer<_BufferType>::GetBufferType() const noexcept
{
    return _BufferType;
}

template <GLenum _BufferType>
void Buffer<_BufferType>::Generate() noexcept
{
    glGenBuffers(1, &m_ID);
}


template class Buffer<GL_ARRAY_BUFFER>;
template class Buffer<GL_ELEMENT_ARRAY_BUFFER>;
