#pragma once

#include "Core/Core.hpp"

struct TextureSettings
{
    GLenum WrapS{ GL_CLAMP_TO_BORDER };
    GLenum WrapT{ GL_CLAMP_TO_BORDER };

    GLenum MinFilter{ GL_NEAREST };
    GLenum MagFilter{ GL_LINEAR };

    bool IsToFlip{ true };

    GLenum StoreColorFormat{ GL_RGB };
    GLenum OriginalColorFormat{ GL_RGB };
};

