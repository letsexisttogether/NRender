#pragma once

#include <cstddef>
#include <cstdint>

#include "Basic/Boundable/Boundable.hpp"

class AttributePointer : public Boundable
{
public:
    using Count = std::uint32_t;
    using IsNormalized = std::uint32_t;
    using Stride = std::size_t;
    using Offset = std::size_t;

public:
    AttributePointer() = default;
    AttributePointer(const AttributePointer&) = delete;
    AttributePointer(AttributePointer&&) = default;

    AttributePointer(const BoundableID id, const Count count,
        const IsNormalized isNormalizzed, const Stride stride,
        const Offset offset, const bool shouldPrepare = true);

    ~AttributePointer() = default;

    void Bind() noexcept override;
    void UnBind() noexcept override;

    AttributePointer& operator = (const AttributePointer&) noexcept = delete;
    AttributePointer& operator = (AttributePointer&&) noexcept = default;

protected:
    void Generate() noexcept override;

private:
    Count m_Count{};
    IsNormalized m_IsNormalized{};
    Stride m_Stride{};
    Offset m_Offset{};
};
