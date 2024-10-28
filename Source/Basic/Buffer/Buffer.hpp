#pragma once

#include <vector>

#include "Basic/Boundable/Boundable.hpp"

template <class _Vertex, const Boundable::Type _Type>
class Buffer : public Boundable
{
public:
    using Count = std::uint16_t;
    using Usage = uint32_t;
    
    using ModernStorage = std::vector<_Vertex>;
    using OldStorage = const _Vertex*;

public:
    Buffer() = delete;
    Buffer(const Buffer&) = delete;
    Buffer(Buffer&&) = default;

    Buffer(const Count maxCount, const Usage usage,
        const bool shouldPrepare = true);

    ~Buffer();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    void AllocateSpace() noexcept;

    void UpdateData(OldStorage data, const Count count, 
        const Count offset) noexcept;
    void UpdateData(const ModernStorage& data, const Count offset)
        noexcept;

    void ClearData(const Count count, const Count offset) noexcept;

    Count GetMaxCount() const noexcept;

protected:
    void Generate() noexcept override;

private:
    Count m_MaxCount{};
    Usage m_Usage{};
};
