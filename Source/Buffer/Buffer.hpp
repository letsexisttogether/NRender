#pragma once

#include <cstdint>
#include <vector>

#include "Boundable/Boundable.hpp"

template <class _DataType, Boundable::Type _BufferType>
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

    Buffer(Data&& data, const bool shouldPrepare = true);

    ~Buffer();

    void FillData() noexcept;

    DataCount GetCount() const noexcept;

private:
    Data m_Data{};
};
