#pragma once

#include "Core/Core.hpp"
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
