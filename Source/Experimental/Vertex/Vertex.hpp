#pragma once

#include <GML/Vector/Definitions.hpp>

#include "Experimental/VAP/VertexAttribPointer.hpp"
#include "Experimental/Vertex/VertexStructure.hpp"

struct Vertex
{
    GML::Vec2f Position{};
};

template <>
struct VertexLayout<Vertex>
{
    static constexpr void SpawnAttributes()
    {
        VertexAttribPointer<Vec2f>
    }
};

/*
struct PosColVertex
{
    GML::Vec2f Position{};
    GML::Vec3f Color{};

    constexpr auto CreateTuple()
    {
        return std::make_tuple(Position, Color);
    };
};

template <typename ... _Types>
inline void SmartCreateVAP()
{
    using DefaultVAP = VertexAttribPointer<void>;

    constexpr std::size_t typesSize = sizeof...(_Types);

    constexpr std::array<DefaultVAP::Size, typesSize> sizes 
    {

    };
};

template <typename _Type>
inline void SmartCreateVAP(const std::uint32_t location, const std::uint32_t size,
    const std::uint32_t offset)
{
    
}

inline void CreateVAP()
{
    using DefaultVAP = VertexAttribPointer<void>;

    constexpr std::array<DefaultVAP::Size, 2> offsets
    {
        offsetof(PosColVertex, Position),
        offsetof(PosColVertex, Color)
    };

    constexpr std::array<DefaultVAP::Size, 2> sizes
    {
        sizeof(PosColVertex::Position),
        sizeof(PosColVertex::Color)
    };

    constexpr std::array<GLenum, 2> glTypes
    {
        GetGLType<GML::Vec2f>(),
        GetGLType<GML::Vec3f>(),
    };

    for (std::int32_t i = 0; i < offsets.size(); ++i)
    {
        DefaultVAP 
        {
            static_cast<uint32_t>(i), sizes[i], glTypes[i], false,
            sizeof(PosColVertex), offsets[i]
        };
    };
}

template <class _BaseVertex, class _InstanceVertex>
class VertexInstance
{
public:
    VertexInstance() = delete;

    VertexInstance(const std::vector<_BaseVertex> baseData,
        const std::vector<_InstanceVertex> instances);

    ~VertexInstance() = default;

private:
    VertexBufferObject m_VAO;
};

template <class _BaseVertex, class _InstanceVertex>
VertexInstance<_BaseVertex, _InstanceVertex>::VertexInstance
    (const std::vector<_BaseVertex> baseData, 
    const std::vector<_InstanceVertex> instances)
    : m_VAO{ true }
{
    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(baseData, GL_STATIC_DRAW);

    /*
        VertexAttribPointer vap0
        {
            0, sizeof(_BaseVertex::FirstMember), 
            GetGLType<_BaseVertex::FirstMember>(),
            false, sizeof(_BaseVertex), offsetof(_BaseVertex:FirstMember)
            
        };
    */

    VertexBufferObject instancedVBO{ true };
    instancedVBO.SetData(instances, GL_STATIC_DRAW);
}
*/

