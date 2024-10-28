#pragma once

#include "Basic/Buffer/VertexBuffer.hpp"
#include "Basic/Texture/Texture.hpp"
#include "Basic/VertexArray/VertexArray.hpp"
#include "Shape/Shape.hpp"
#include "Utility/Naming.hpp"

NRenderSpaceStart

class Sprite
{
public:
    Sprite() = delete;
    Sprite(const Sprite&) = delete;
    Sprite(Sprite&&) = default;

    Sprite(Shape&& shape, Shape&& textureBounds, const ID textureID,
        const ID shaderID);

    VertexArray& GetVAO() noexcept;

    ID GetTextureID() const noexcept;
    ID GetShaderID() const noexcept;

    ~Sprite() = default;

private:
    Vertex2DBuffer::Count CreateVBO(Shape&& shape, Shape&& textureBounds) noexcept;
    void CreateEBO(const Vertex2DBuffer::Count count) noexcept;
    void CreateAttributes(const Vertex2DBuffer::Count count) noexcept;

private:
    VertexArray m_VAO{};

    ID m_TextureID;
    ID m_ShaderID;
};

NRenderSpaceEnd
