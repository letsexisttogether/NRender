#include "GetGLType.hpp"

#include <GML/Vector/Definitions.hpp>
#include <cstdint>
#include <type_traits>

template <>
GLenum GetGLType<std::int8_t>() noexcept
{ 
    return GL_BYTE;
}

template <>
GLenum GetGLType<std::uint8_t>() noexcept
{ 
    return GL_UNSIGNED_BYTE;
}

template <>
GLenum GetGLType<std::int16_t>() noexcept
{ 
    return GL_SHORT;
}

template <>
GLenum GetGLType<std::uint16_t>() noexcept
{ 
    return GL_UNSIGNED_SHORT;
}

template <>
GLenum GetGLType<std::int32_t>() noexcept
{ 
    return GL_INT;
}

template <>
GLenum GetGLType<std::uint32_t>() noexcept
{ 
    return GL_UNSIGNED_INT;
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


#define DefineGetGLTypeVec(size, abbreviation) \
    template <> \
    GLenum GetGLType<GML::Vec##size##abbreviation>() noexcept \
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
