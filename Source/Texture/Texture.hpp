#pragma once

#include "Boundable/Boundable.hpp"
#include "Texture/TexFillParams.hpp"

class Texture : public Boundable
{
public:
    using Color = std::uint8_t;
    using Resolution = std::int32_t;

    // Change the Data type
    using Data = Color*;
    using Slot = std::int32_t;

public:
    Texture() = delete; 
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;

    Texture(Data const data, const Resolution width, const Resolution height,
        const TexFillParams& fillParams, const Slot slot,
        const bool shouldPrepare = true);

    ~Texture();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    void SetParameters() noexcept;
    void FillData() noexcept;

    Slot GetSlot() const noexcept;

    Texture& operator = (const Texture&) = delete;
    Texture& operator = (Texture&&) = delete;

protected:
    void Generate() noexcept override;

private:
    Data m_Data{};

    Resolution m_Width{};
    Resolution m_Height{};

    TexFillParams m_FillParams{};
    Slot m_Slot{};

};
