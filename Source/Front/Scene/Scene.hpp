#pragma once

#include <unordered_map>

#include "Front/IDable/IDable.hpp"
#include "Front/Chunk/Manager/ChunkManager.hpp"
#include "Front/GameObject/GameObject.hpp"

class Scene
{
public:
    using Objects = std::unordered_map<IDable::ID, GameObject>;

public:
    Scene() = default;
    Scene(const Scene&) = default;
    Scene(Scene&&) = default;

    ~Scene() = default;

    void AddObject(GameObject&& object) noexcept;

    Scene& operator = (const Scene&) noexcept = delete;
    Scene& operator = (Scene&&) noexcept = delete;

private:
    // TODO: Move to a dedicated class
    IDable::ID GetNextID() const noexcept;

private:
    Objects m_Objects{};
    ChunkManager m_ChunkManager{};
};
