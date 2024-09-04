#pragma once

#include "Basic/Buffer/IndexBuffer.hpp"
#include "Basic/Buffer/VertexBuffer.hpp"
#include "Basic/VertexArray/VertexArray.hpp"
#include "Front/GameObject/GameObject.hpp"
#include "Front/Primitive/Base/Rectangle/Rectangle.hpp"

class DrawableRectangle : public Rectangle, public GameObject
{
public:
    DrawableRectangle() = delete;
    DrawableRectangle(const DrawableRectangle&) = delete;
    DrawableRectangle(DrawableRectangle&&) = default;

    DrawableRectangle(Rectangle&& coordinates, const Rectangle& textureCoords);

    ~DrawableRectangle() = default;

    void Draw() noexcept override;

private:
    VertexArray m_VAO{};
    Vertex2DBuffer m_VBO{ 8, GL_STATIC_DRAW };
    IndexBuffer m_EBO{ 6, GL_STATIC_DRAW };
};
