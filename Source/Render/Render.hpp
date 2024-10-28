#pragma once

// #include "Basic/GPUProgram/GPUProgram.hpp"
#include <cstdint>
#include <unordered_map>

#define GLEW_STATIC
#include <GLEW/glew.h>

#include "Sprite/Sprite.hpp"

NRenderSpaceStart

class Render
{
public:
    static void Init() noexcept;

    static ID AddSprite(Sprite&& sprite) noexcept;

    static void DrawSprite(const ID spriteID) noexcept;

    static void ClearSprites() noexcept;

private:
    /*
    using Sprites = std::unordered_map<ID, Sprite>;
    using Shaders = std::unordered_map<ID, GPUProgram>;
    */

private:
    static void InitGLEW() noexcept;

    // TODO: Add new params
    static void Draw(const std::size_t count) noexcept;

private:
    inline static bool s_IsInit{ false };

    /*
    inline static Sprites m_Sprites{};
    inline static Shaders m_Shaders{};

        inline static std::unordered_set<Sprite> s_Single{};
        inline static std::unordered_multimap<ID, Batch> s_Batched{};
        inline static std::vector<Instance> s_Instanced{};
    */
};

NRenderSpaceEnd
