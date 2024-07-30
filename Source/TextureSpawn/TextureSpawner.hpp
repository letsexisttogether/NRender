#pragma once

#include <string>

#include "Texture/TexFillParams.hpp"
#include "Texture/Texture.hpp"

class TextureSpawner
{
public:
    using TexturePath = std::string;
    
public:
    TextureSpawner() = delete;
    TextureSpawner(const TextureSpawner&) = default;
    TextureSpawner(TextureSpawner&&) = default;

    TextureSpawner(const TexFillParams& fillParams, const Texture::Slot slot);

    ~TextureSpawner() = default;

    Texture LoadTexture(const TexturePath& path) noexcept;

private:
    void MakeVerticalProper() noexcept;

private:
    TexFillParams m_FillParams{};
    Texture::Slot m_Slot{};
};
