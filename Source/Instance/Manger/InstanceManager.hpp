#pragma once

#include <queue>
#include <unordered_map>
#include <any>

#include "Instance/InstanceSource.hpp"

class InstanceManager
{
public:
    InstanceManager();
    InstanceManager(const InstanceManager&) = delete;
    InstanceManager(InstanceManager&&) = default;

    ~InstanceManager() = default;
    

    template <class _BaseVertex, class _InstanceVertex>
   std::size_t AddInstance(InstanceSource<_BaseVertex,
        _InstanceVertex>&& instance) noexcept;

    template <class _BaseVertex, class _InstanceVertex>
    InstanceSource<_BaseVertex, _InstanceVertex>& GetInstance
        (const std::size_t ID) noexcept;


private:
    std::unordered_map<std::size_t, std::any> m_Instances{};
    std::queue<std::size_t> m_FreeIDs{};
};

InstanceManager::InstanceManager()
{
    m_FreeIDs.push(0);
}

template <class _BaseVertex, class _InstanceVertex>
std::size_t InstanceManager::AddInstance(InstanceSource<_BaseVertex,
    _InstanceVertex>&& instance) noexcept
{
    const std::size_t freeID = m_FreeIDs.front();
    m_FreeIDs.pop();

    m_Instances[freeID] = std::make_any<InstanceSource<_BaseVertex,
        _InstanceVertex>>(std::move(instance));

    m_FreeIDs.push(freeID + 1);

    return freeID;
}


template <class _BaseVertex, class _InstanceVertex>
InstanceSource<_BaseVertex, _InstanceVertex>& InstanceManager::
    GetInstance(const std::size_t ID) noexcept
{
    auto& instance = m_Instances[ID];

    return std::any_cast<InstanceSource<_BaseVertex, _InstanceVertex>&>(instance);
};
