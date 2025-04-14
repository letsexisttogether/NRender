#pragma once

#include <cstdint>

class Boundable
{
public:
    Boundable() = default;
    Boundable(const Boundable&) = delete;
    Boundable(Boundable&& boundable);

    ~Boundable() = default;

    virtual void Bind() noexcept = 0;
    virtual void Unbind() noexcept = 0;

    std::int32_t GetID() const noexcept;

protected:
    void Init(const bool shouldBind = true) noexcept;

    virtual void Generate() noexcept = 0;

protected:
    std::uint32_t m_ID{};
};
