#include "Scene.hpp"
#include <utility>

void Scene::AddObject(GameObject&& object) noexcept
{
    const IDable::ID objectID = GetNextID();

    m_Objects.insert({ objectID, std::move(object) });

    m_ChunkManager.DistributeObject(objectID);
}
