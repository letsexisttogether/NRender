#include "Texture.hpp"

#include <array>
#include <cassert>
#include <regex>
#include <string_view>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GML/Vector/Definitions.hpp>

#include "Core/Core.hpp"
#include "Utility/Convert/GetGLType.hpp"

Texture::Texture(const std::filesystem::path& path, const GLenum slot,
    const GLenum type, const TextureSettings& settings) noexcept
    : m_Path{ path }, m_Slot{ slot }, m_Type{ type }, m_Settings{ settings }
{
    // TODO: Move the reading functionality to a dedicated class
    assert(std::filesystem::exists(path)
        && "The texture file does not exsit");
    
    Init(true);  
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Texture::Bind() noexcept
{
    glBindTexture(m_Type, m_ID); 
}

void Texture::Unbind() noexcept
{
    glBindTexture(m_Type, 0);
}

void Texture::Generate() noexcept
{
    glGenTextures(1, &m_ID);
    Bind();

    ApplySettings();
    SetImageData();
}

void Texture::ApplySettings() noexcept
{
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_S, m_Settings.WrapS);
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_T, m_Settings.WrapT);

    if (constexpr GLenum clampToBorder = GL_CLAMP_TO_BORDER;
        m_Settings.WrapS == clampToBorder || m_Settings.WrapT == clampToBorder)
    {
        glTexParameterfv(m_Type, GL_TEXTURE_BORDER_COLOR,
            s_BorderColor.data());
    }

    glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER, m_Settings.MinFilter);
    glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER, m_Settings.MagFilter);
}

void Texture::SetImageData() noexcept
{
    std::int32_t width{};
    std::int32_t height{};
    std::int32_t nrChannels{};

    stbi_set_flip_vertically_on_load(m_Settings.IsToFlip);

    // TODO: Change it to something better
    const std::string cPath{ m_Path.string() };

    std::uint8_t* textureRawData = stbi_load(cPath.c_str(), &width, &height,
        &nrChannels, 0);

    assert(textureRawData && "The data was not loaded properly");

    glTexImage2D(m_Type, 0, m_Settings.StoreColorFormat,
        width, height, 0, m_Settings.OriginalColorFormat,
        GetGLType<std::uint8_t>(), textureRawData);

    stbi_image_free(textureRawData);
}
