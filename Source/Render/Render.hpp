#pragma once

#include "Core/Core.hpp"
#include "Utility/Namespace.hpp"
#include "Experimental/Sprite/Sprite.hpp"

NRenderSpaceStart

class Render
{
public:
    static void Init() noexcept;

    static void DrawSprite(Sprite& sprite);

private:
    static void InitGLEW() noexcept;

private:
    inline static bool s_IsInit{ false };
};

NRenderSpaceEnd
