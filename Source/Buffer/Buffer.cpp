#include "Buffer.hpp"

#include <GLEW/glew.h>

#define Template template <class _DataType, Boundable::Type _BufferType>
#define BufferT Buffer<_DataType, _BufferType>
#define BufferTDef(returnType) Template \
    returnType BufferT

BufferTDef()::Buffer(Data&& data, const bool shouldPrepare)
    : Boundable{ _BufferType }, m_Data{ std::move(data) }
{
    Generate();

    if (shouldPrepare)
    {   
        Bind();
        FillData();
    }
}

BufferTDef()::~Buffer()
{
    UnBind();

    glDeleteBuffers(1, &m_ID);
}

BufferTDef(void)::Buffer::FillData() noexcept
{
    glBufferData(m_Type, m_Data.size() * sizeof(_DataType),
        m_Data.data(), GL_STATIC_DRAW);
}

BufferTDef(typename BufferT::DataCount)::GetCount()
    const noexcept
{
    return m_Data.size();
}

template class Buffer<std::uint32_t, GL_ELEMENT_ARRAY_BUFFER>;
template class Buffer<float, GL_ARRAY_BUFFER>;
