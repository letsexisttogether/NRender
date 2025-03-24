#include "Sprite.hpp"

#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"

Sprite::Sprite(const Shape& shape)
{
    VertexBufferObject VBO{ true };
    ElementBufferObject EBO{ true };

    VBO.SetData(shape.GetVertices(), GL_STATIC_DRAW);
    EBO.SetData(shape.GetIndices(), GL_STATIC_DRAW);

    VertexAttribPointer<float> vap0
    {
        0, 2, GL_FLOAT, false, 5, 0
    };

    VertexAttribPointer vap1
    {
        vap0.SpawnNext(3)
    };

    VAO.Unbind();
}

VertexArrayObject& Sprite::GetVAO() noexcept
{
    return VAO;
}
