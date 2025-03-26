#pragma once

#include <GML/Vector/Definitions.hpp>
#include <cstdint>

#include "Core/Core.hpp"

// NOTE: I want it to be a set of functions and not a class for now
// I may change it in the future, but as for now I like it this way

template <typename _PrimitiveType>
constexpr GLenum GetGLType() noexcept;

template <>
constexpr GLenum GetGLType<std::int8_t>() noexcept
{ 
    return GL_BYTE;
}

template <>
constexpr GLenum GetGLType<std::uint8_t>() noexcept
{ 
    return GL_UNSIGNED_BYTE;
}

template <>
constexpr GLenum GetGLType<std::int16_t>() noexcept
{ 
    return GL_SHORT;
}

template <>
constexpr GLenum GetGLType<std::uint16_t>() noexcept
{ 
    return GL_UNSIGNED_SHORT;
}

template <>
constexpr GLenum GetGLType<std::int32_t>() noexcept
{ 
    return GL_INT;
}

template <>
constexpr GLenum GetGLType<std::uint32_t>() noexcept
{ 
    return GL_UNSIGNED_INT;
}

template <>
constexpr GLenum GetGLType<float>() noexcept
{ 
    return GL_FLOAT;
}

template <>
constexpr GLenum GetGLType<double>() noexcept 
{ 
    return GL_DOUBLE; 
}


#define DefineGetGLTypeVec(size, abbreviation) \
    template <> \
    constexpr GLenum GetGLType<GML::Vec##size##abbreviation>() noexcept \
    { \
        using BaseType = std::remove_extent_t \
            <GML::Vec##size##abbreviation::Data>; \
        \
        return GetGLType<BaseType>(); \
    } \

#define DeclareGetGLTypeVec(size) \
    DefineGetGLTypeVec(size, b) \
    DefineGetGLTypeVec(size, ub) \
    \
    DefineGetGLTypeVec(size, s) \
    DefineGetGLTypeVec(size, us) \
    \
    DefineGetGLTypeVec(size, i) \
    DefineGetGLTypeVec(size, ui) \
    \
    DefineGetGLTypeVec(size, f) \
    DefineGetGLTypeVec(size, d) \

DeclareGetGLTypeVec(2);
DeclareGetGLTypeVec(3);
DeclareGetGLTypeVec(4);

#undef DeclareGetGLTypeVec
#undef DefineGetGLTypeVec
