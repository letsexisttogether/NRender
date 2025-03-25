#pragma once

#include "Core/Core.hpp"

class VertexAttribPointerManager
{
    VertexAttribPointerManager() = default;
    VertexAttribPointerManager(const VertexAttribPointerManager&) = delete;
    VertexAttribPointerManager(VertexAttribPointerManager&&) = delete;

    ~VertexAttribPointerManager() = default;

    template <typename _PrimitiveType>
    static GLenum GetType() noexcept;
};

