#pragma once

#include <cstdint>

#include <GL/glew.h>

class TexFillParams 
{
public:
    using PixelDiversity = std::int32_t;
    using ColorType = std::uint32_t;

public:
    PixelDiversity InternalFormat{ GL_RGB };
    PixelDiversity InputFormat{ GL_RGB };
    ColorType Type{ GL_UNSIGNED_BYTE };

};
