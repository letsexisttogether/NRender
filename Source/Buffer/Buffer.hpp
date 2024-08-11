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
    Buffer() = default;
    Buffer(const Buffer&) = default;
    Buffer(Buffer&&) = default;

    Buffer(Data&& data, const bool shouldPrepare = true);

    ~Buffer();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    void FillData() noexcept;

    DataCount GetCount() const noexcept;

    // Just for one function implemention process 
    Data& GetRawData() noexcept { return m_Data; }

    Buffer& operator = (const Buffer&) noexcept = default;
    Buffer& operator = (Buffer&& buffer) noexcept = default;

protected:
    void Generate() noexcept override;

private:
    Data m_Data{};
};
