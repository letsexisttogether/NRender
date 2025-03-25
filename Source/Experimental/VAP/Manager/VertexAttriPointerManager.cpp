#include "VertexAttriPointerManager.hpp"

#include <cstdint>

template <>
GLenum VertexAttribPointerManager::GetType<std::uint8_t>() noexcept
{ 
    return GL_UNSIGNED_BYTE;
}

template <>
GLenum VertexAttribPointerManager::GetType<std::int8_t>() noexcept
{ 
    return GL_BYTE;
}

template <>
GLenum VertexAttribPointerManager::GetType<std::uint16_t>() noexcept
{ 
    return GL_UNSIGNED_SHORT;
}

template <>
GLenum VertexAttribPointerManager::GetType<std::int16_t>() noexcept
{ 
    return GL_SHORT;
}

template <>
GLenum VertexAttribPointerManager::GetType<std::uint32_t>() noexcept
{ 
    return GL_UNSIGNED_INT;
}

template <>
GLenum VertexAttribPointerManager::GetType<std::int32_t>() noexcept
{ 
    return GL_INT;
}

template <>
GLenum VertexAttribPointerManager::GetType<float>() noexcept
{ 
    return GL_FLOAT;
}

template <>
GLenum VertexAttribPointerManager::GetType<double>() noexcept 
{ 
    return GL_DOUBLE; 
}
