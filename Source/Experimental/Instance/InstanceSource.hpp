#pragma once

#include <algorithm>
#include <vector>

#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"
#include "Experimental/Vertex/VertexLayout.hpp"

template <class _BaseVertex, class _InstanceVertex>
class InstanceSource
{
public:
    using BaseData = std::vector<_BaseVertex>;
    using Instances = std::vector<_InstanceVertex>;

public:
    InstanceSource() = delete;
    InstanceSource(const InstanceSource&) = delete;
    InstanceSource(InstanceSource&&) = default;

    InstanceSource(const BaseData& baseData, Instances&& instances);

    ~InstanceSource() = default;

    const _InstanceVertex& GetInstance(const std::size_t ID) const noexcept;
    void SetInstance(const std::size_t ID, _InstanceVertex&& vertex) noexcept;

    VertexArrayObject& GetVAO() noexcept;

    std::size_t GetBaseSize() const noexcept;
    std::size_t GetInstancesSize() const noexcept;

    InstanceSource& operator = (const InstanceSource&) = delete;
    InstanceSource& operator = (InstanceSource&&) = delete;

private:
    VertexArrayObject m_VAO{ true };
    VertexBufferObject m_InstancedVBO{ false };

    std::size_t m_BaseSize;

    Instances m_Instances;
};


template <class _BaseVertex, class _InstanceVertex>
InstanceSource<_BaseVertex, _InstanceVertex>::InstanceSource
    (const BaseData& baseData, Instances&& instances)
    : m_BaseSize{ baseData.size() }, m_Instances{ std::move(instances) }
{
    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(baseData, GL_STATIC_DRAW);

    auto baseAttrributes = VertexLayout<_BaseVertex>::SpawnAttributes();

    m_InstancedVBO.Bind();
    m_InstancedVBO.SetData(m_Instances, GL_DYNAMIC_DRAW);

    auto intancedAttributes = VertexLayout<_InstanceVertex>::
        SpawnAttributes(baseAttrributes.size());

    for (auto& attribute : intancedAttributes)
    {
        attribute.SetDivisor(1);
    }

    m_VAO.Unbind();
}

template <class _BaseVertex, class _InstanceVertex>
const _InstanceVertex& InstanceSource<_BaseVertex, _InstanceVertex>::
    GetInstance(const std::size_t ID) const noexcept
{
    assert(m_Instances.size() > ID
        && "[Instance::GetInstance] Unallowed index");

    return m_Instances[ID];
}

template <class _BaseVertex, class _InstanceVertex>
void InstanceSource<_BaseVertex, _InstanceVertex>::
    SetInstance(const std::size_t ID, _InstanceVertex&& vertex) noexcept
{
    assert(m_Instances.size() > ID
        && "[Instance::GetInstance] Unallowed index");

    m_InstancedVBO.Bind();

    _InstanceVertex& instance = m_Instances[ID];
    instance = std::move(vertex);

    m_InstancedVBO.SetSubData(instance, sizeof(instance) * ID);

    m_InstancedVBO.Unbind();
}


template <class _BaseVertex, class _InstanceVertex>
VertexArrayObject& InstanceSource<_BaseVertex, _InstanceVertex>::
    GetVAO() noexcept
{
    return m_VAO;
}

template <class _BaseVertex, class _InstanceVertex>
std::size_t InstanceSource<_BaseVertex, _InstanceVertex>::
    GetBaseSize() const noexcept
{
    return m_BaseSize;
}

template <class _BaseVertex, class _InstanceVertex>
std::size_t InstanceSource<_BaseVertex, _InstanceVertex>::
    GetInstancesSize() const noexcept
{
    return m_Instances.size();
}
