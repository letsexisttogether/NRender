#include "Square.hpp"

Square::Square(const Position origin, const Size size)
    : Rectangle{ origin, size, size }, Primitive{}
{
    Generate();         
}

void Square::Generate() noexcept
{
    Vertex2DBuffer vertices 
    {
        CalculateBoundries()
    };

    IndexBuffer indices
    {
        {
            0, 1, 2,
            1, 2, 3
        }
    };

    SetVertices(std::move(vertices));
    SetIndices(std::move(indices));

    m_Attributes.push_back({ 0, 2, GL_FALSE, 4, 0 });
    m_Attributes.push_back({ 1, 2, GL_FALSE, 4, 2 });
}
