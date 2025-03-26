#include "GetGLType.hpp"

#include <cstdint>

template <>
GLenum GetGLType<std::uint8_t>() noexcept
{ 
    return GL_UNSIGNED_BYTE;
}

template <>
GLenum GetGLType<std::int8_t>() noexcept
{ 
    return GL_BYTE;
}

template <>
GLenum GetGLType<std::uint16_t>() noexcept
{ 
    return GL_UNSIGNED_SHORT;
}

template <>
GLenum GetGLType<std::int16_t>() noexcept
{ 
    return GL_SHORT;
}

template <>
GLenum GetGLType<std::uint32_t>() noexcept
{ 
    return GL_UNSIGNED_INT;
}

template <>
GLenum GetGLType<std::int32_t>() noexcept
{ 
    return GL_INT;
}

template <>
GLenum GetGLType<float>() noexcept
{ 
    return GL_FLOAT;
}

template <>
GLenum GetGLType<double>() noexcept 
{ 
    return GL_DOUBLE; 
}
