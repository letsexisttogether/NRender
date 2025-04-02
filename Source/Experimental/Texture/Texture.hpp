#pragma once

#include <filesystem>
#include <array>

#include "Core/Core.hpp"
#include "Experimental/Boundable/Boundable.hpp"
#include "Experimental/Texture/TextureSettings.hpp"

class Texture : protected Boundable
{
public:
    Texture() = delete;
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;

    Texture(const std::filesystem::path& path, const GLenum slot,
        const GLenum type, const TextureSettings& settings) noexcept;

    ~Texture();

    void Bind() noexcept override;
    void Unbind() noexcept override;

protected:
    void Generate() noexcept override;

private:
    void ApplySettings() noexcept;
    void SetImageData() noexcept;

private:
    static constexpr std::array<float, 4> s_BorderColor
    {
        1.0f, 1.0f, 0.0f, 1.0f
    };

private:
    std::filesystem::path m_Path{};
    GLenum m_Slot{};
    GLenum m_Type{};
    TextureSettings m_Settings{};
};
