#pragma once

#include <cstdint>
#include <vector>

#include "Boundable/Boundable.hpp"

class VertexBuffer : public Boundable
{
public:
    using BufferID = std::uint32_t;
    using DataType = float;
    using Data = std::vector<DataType>;
    using DataCount = typename Data::size_type;

public:
    VertexBuffer() = delete;
    VertexBuffer(const VertexBuffer&) = default;
    VertexBuffer(VertexBuffer&&) = default;

    VertexBuffer(Data&& data);

    ~VertexBuffer() = default;

    void FillData() noexcept;

    DataCount GetCount() const noexcept;

private:
    Data m_Data{};
};
