#pragma once

#include <cstdint>
#include <vector>

#include "GLEW/glew.h"
#include "Boundable/Boundable.hpp"

#define Template template <class _DataType, Boundable::Type _BufferType>
#define BufferT Buffer<_DataType, _BufferType>
#define BufferTDef(returnType) Template \
    returnType BufferT

Template 
class Buffer : public Boundable
{
public:
    using BufferID = std::uint32_t;
    using Data = std::vector<_DataType>;
    using DataCount = typename Data::size_type;

public:
    Buffer() = delete;
    Buffer(const Buffer&) = default;
    Buffer(Buffer&&) = default;

    Buffer(Data&& data);

    ~Buffer();

    void FillData() noexcept;

    DataCount GetCount() const noexcept;

private:
    Data m_Data{};
};


BufferTDef()::Buffer(Data&& data)
    : Boundable{ _BufferType }, m_Data{ std::move(data) }
{
    Generate();
}


BufferTDef()::~Buffer()
{
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


#undef BufferTDef
#undef BufferT
#undef Template
