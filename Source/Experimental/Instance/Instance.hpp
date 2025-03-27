#pragma once

#include <vector>

#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"

template <class _DataType>
class Instance
{
public:
    Instance() = default;
    Instance(const Instance&) = delete;
    Instance(Instance&&) = default;

    Instance(const std::vector<float>& baseData,
        const std::vector<_DataType>& perInstanceData);

    ~Instance() = default;

    VertexArrayObject& GetVAO() noexcept;

    Instance& operator = (const Instance&) = default;
    Instance& operator = (Instance&&) = default;

private:
    VertexArrayObject m_VAO;
};


template <class _DataType>
Instance<_DataType>::Instance(const std::vector<float>& baseData,
    const std::vector<_DataType>& perInstanceData)
    : m_VAO{ true }
{
    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(baseData, GL_STATIC_DRAW);

    VertexAttribPointer<float> vertexVAP 
    {
        0, 2, GL_FLOAT, false, 5, 0
    };

    VertexAttribPointer<float> colorVAP
    {
        vertexVAP.SpawnNext<float>(3)
    };

    VertexBufferObject instanceVBO{ true };
    instanceVBO.SetData(perInstanceData, GL_STATIC_DRAW);

    VertexAttribPointer<_DataType> instanceVAP
    {
        2, 2, GL_FLOAT, false, 2, 0
    };
    instanceVAP.SetDivisor(1);

    m_VAO.Unbind();
}

template <class _DataType>
VertexArrayObject& Instance<_DataType>::GetVAO() noexcept
{
    return m_VAO;
}
