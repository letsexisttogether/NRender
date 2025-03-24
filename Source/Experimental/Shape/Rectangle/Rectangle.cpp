#include "Rectangle.hpp"

Rectangle::Rectangle(const Vertex a, const Vertex b,
    const Vertex c, const Vertex d)
{
    m_Vertices = Vertices
    { 
        a.Coordinates.X(), a.Coordinates.Y(),
        b.Coordinates.X(), b.Coordinates.Y(),
        c.Coordinates.X(), c.Coordinates.Y(),
        d.Coordinates.X(), d.Coordinates.Y(),
    };

    m_Indices = { 0, 1, 2, 1, 3, 2 };
}

Rectangle::Rectangle(const ColoredVertex a, const ColoredVertex b,
    const ColoredVertex c, const ColoredVertex  d)
{
    m_Vertices = Vertices
    { 
        a.Coordinates.X(), a.Coordinates.Y(),
        a.Color.X(), a.Color.Y(), a.Color.Z(),

        b.Coordinates.X(), b.Coordinates.Y(),
        b.Color.X(), b.Color.Y(), b.Color.Z(),

        c.Coordinates.X(), c.Coordinates.Y(),
        c.Color.X(), c.Color.Y(), c.Color.Z(),

        d.Coordinates.X(), d.Coordinates.Y(),
        d.Color.X(), d.Color.Y(), d.Color.Z(),
    };

    m_Indices = { 0, 1, 2, 1, 3, 2 };
}
