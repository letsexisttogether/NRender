#include "Triangle.hpp"

Triangle::Triangle(const Vertex a, const Vertex b, const Vertex c)
{
    m_Vertices = Vertices
    { 
        a.Coordinates.X(), a.Coordinates.Y(),
        b.Coordinates.X(), b.Coordinates.Y(),
        c.Coordinates.X(), c.Coordinates.Y(),
    };

    m_Indices = Indices{ 0, 1, 2 };
}

Triangle::Triangle(const ColoredVertex a, const ColoredVertex b,
    const ColoredVertex c)
{
    m_Vertices = Vertices
    {
        a.Coordinates.X(), a.Coordinates.Y(),
        a.Color.X(), a.Color.Y(), a.Color.Z(),

        b.Coordinates.X(), b.Coordinates.Y(),
        b.Color.X(), b.Color.Y(), b.Color.Z(),

        c.Coordinates.X(), c.Coordinates.Y(),
        c.Color.X(), c.Color.Y(), c.Color.Z(),
    };

    m_Indices = Indices{ 0, 1, 2 };
}
