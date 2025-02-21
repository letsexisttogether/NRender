#include "TextureSpawner.hpp"

#include <GL/glew.h>
#include <stb_image.h>

TextureSpawner::TextureSpawner(const TexFillParams& fillParams,
    const Texture::Slot slot)
    : m_FillParams{ fillParams }, m_Slot{ slot }
{
    MakeVerticalProper();
}

Texture TextureSpawner::LoadTexture(const TexturePath& path) noexcept
{
    Texture::Resolution width{};
    Texture::Resolution height{};
    Texture::Resolution nrChannels{};
    Texture::Data data = stbi_load(path.c_str(), &width, &height,
        &nrChannels, 0);

    Texture texture{ data, width, height, m_FillParams, m_Slot };

    ++m_Slot;

    return texture;
}

void TextureSpawner::MakeVerticalProper() noexcept
{
    stbi_set_flip_vertically_on_load(true); 
}
