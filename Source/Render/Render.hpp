#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "Utility/Namespace.hpp"


NRenderSpaceStart

class Render
{
public:
    static void Init() noexcept;

private:
    static void InitGLEW() noexcept;

private:
    inline static bool s_IsInit{ false };
};

NRenderSpaceEnd
