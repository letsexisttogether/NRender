#pragma once

#include "Experimental/Shape/Shape.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"

class Sprite
{
public:
    Sprite() = delete;
    Sprite(const Sprite&) = delete;
    Sprite(Sprite&&) = default;

    Sprite(const Shape& shape);

    ~Sprite() = default; 

    VertexArrayObject& GetVAO() noexcept;

    Sprite& operator = (const Sprite&) = delete;
    Sprite& operator = (Sprite&&) = delete;

private:
    VertexArrayObject VAO{ true };
};
