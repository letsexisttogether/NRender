#include "Scene.hpp"

#include <cassert>


Scene::~Scene()
{
    for (auto& [id, object] : m_Objects)
    {
        delete object;
    }
}

GameObject* Scene::GetObject(const IDGenerator::ID id) 
    noexcept
{
    auto iter = m_Objects.find(id);
    
    assert(iter != m_Objects.end() && "The object was not found");

    return iter->second;
}
