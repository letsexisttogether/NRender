#include "Buffer.hpp"

#include <GLEW/glew.h>
#include <GML/Vector/Definitions.hpp>

#define Template template <class _Vertex, Boundable::Type _Type>
#define BufferT Buffer<_Vertex, _Type>
#define BufferTDef(returnType) Template \
    returnType BufferT

BufferTDef()::Buffer(const Count maxCount, const Usage usage,
    const bool shouldPrepare)
    : Boundable{ _Type }, m_MaxCount{ maxCount }, m_Usage{ usage }
{
    Generate();

    if (shouldPrepare)
    {
        Bind();
        AllocateSpace();
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

BufferTDef(void)::AllocateSpace() noexcept
{
    glBufferData(m_Type, sizeof(_Vertex) * m_MaxCount, nullptr, m_Usage);
}

BufferTDef(void)::UpdateData(OldStorage data, const Count count, 
    const Count offset) noexcept
{
    if (count + offset > m_MaxCount)
    {
        return;
    }

    glBufferSubData(m_Type, offset * sizeof(_Vertex),
        count * sizeof(_Vertex), data);
}

BufferTDef(void)::UpdateData(const ModernStorage& data, const Count offset)
    noexcept
{
    UpdateData(data.data(), data.size(), offset);
}

BufferTDef(void)::ClearData(const Count count, const Count offset) noexcept
{
    // TODO: probably implement this methods
}

BufferTDef(typename BufferT::Count)::GetMaxCount() const noexcept
{
    return m_MaxCount;
}

BufferTDef(void)::Generate() noexcept
{
    glCreateBuffers(1, &m_ID);
}


template class Buffer<GML::Vec2f, GL_ARRAY_BUFFER>;
template class Buffer<std::uint32_t, GL_ELEMENT_ARRAY_BUFFER>;
