#pragma once

#include "Basic/Boundable/Boundable.hpp"

class VertexArray : public Boundable 
{
public:
    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&&) = default;

    VertexArray(const bool shouldPrepare = true);

    ~VertexArray();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    VertexArray& operator = (const VertexArray&) noexcept = delete;
    VertexArray& operator = (VertexArray&&) noexcept = default;

protected:
    // Consider moving to Boundable or the global space
    static inline BoundableID m_CurrentBoundID{};

protected:
    void Generate() noexcept override;
};
