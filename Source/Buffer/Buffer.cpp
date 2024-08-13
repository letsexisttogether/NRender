#include "Buffer.hpp"

#include <GLEW/glew.h>
#include <GML/Vector/Definitions.hpp>
#include <iostream>

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
    glDeleteBuffers(1, &m_ID);
}

BufferTDef(void)::Bind() noexcept
{
    glBindBuffer(m_Type, m_ID);
}

BufferTDef(void)::UnBind() noexcept
{
    glBindBuffer(m_Type, 0);
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

BufferTDef(void)::Generate() noexcept 
{
    glGenBuffers(1, &m_ID);
}

template class Buffer<GML::Vec2f, GL_ARRAY_BUFFER>;
template class Buffer<std::uint32_t, GL_ELEMENT_ARRAY_BUFFER>;
