#pragma once

#include <GML/Vector/Definitions.hpp>
#include <cstdlib>

template <class _InstanceVertex>
class Instance
{
public:
    Instance() = delete;

    struct _Vertex
    {
        GML::Vec2f Scale{};
        GML::Vec2f UV{};
    };

private:
    std::size_t m_Index{};
    std::size_t Offset = m_Index * sizeof(_Vertex);
};
