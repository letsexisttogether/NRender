#include "Texture.hpp"

#include <iostream>

#include "GLEW/glew.h"

Texture::Texture(Data const data, const Resolution width,
    const Resolution height, const TexFillParams& fillParams, const Slot slot,
    const bool shouldPrepare)
    : Boundable{ GL_TEXTURE_2D }, m_Data{ data }, m_Width{ width }, 
    m_Height{ height }, m_FillParams{ fillParams }, m_Slot{ slot }
{
    Generate();

    if (shouldPrepare)
    {
        Bind();
        SetParameters();
        FillData();
    }
}

Texture::~Texture()
{
    delete m_Data;
}

void Texture::SetParameters() noexcept
{
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_T, GL_LINEAR);

    glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER,
        GL_LINEAR);
}

void Texture::FillData() noexcept
{
    if (!m_Data || !m_Width || !m_Height)
    {
        return;
    }

    glTexImage2D(m_Type, 0, m_FillParams.InternalFormat, m_Width, m_Height,
        0, m_FillParams.InputFormat, m_FillParams.Type, m_Data);

    glGenerateMipmap(m_Type);
}

void Texture::Bind() noexcept
{
    glActiveTexture(m_Slot);

    glBindTexture(m_Type, m_ID);
}

void Texture::UnBind() noexcept
{
    glActiveTexture(m_Slot);

    glBindTexture(m_Type, 0);
}

void Texture::Generate() noexcept
{
    glGenTextures(1, &m_ID);
}

Texture::Slot Texture::GetSlot() const noexcept
{
    return m_Slot - GL_TEXTURE0;
}

Texture::Slot Texture::GetRawSlot() const noexcept
{
    return m_Slot;
}
