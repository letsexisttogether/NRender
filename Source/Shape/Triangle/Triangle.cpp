#include "Triangle.hpp"

NRenderSpaceStart

Triangle::Triangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
    m_Vertices.push_back(a);
    m_Vertices.push_back(b);
    m_Vertices.push_back(c);
}

NRenderSpaceEnd
