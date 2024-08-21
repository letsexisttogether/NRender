#pragma once

#include <unordered_map>

#include "Front/IDGenerator/IDGenerator.hpp"
#include "Front/GameObject/GameObject.hpp"

class Scene
{
public:
    Scene() = default;
    Scene(const Scene&) = default;
    Scene(Scene&&) = default;

    virtual ~Scene();

    virtual void AddObject(GameObject* const object) noexcept = 0;

    GameObject* GetObject(const IDGenerator::ID id) noexcept;

    virtual void UpdateLogic() noexcept = 0;
    virtual void UpdateGraphics() noexcept = 0;

    Scene& operator = (const Scene&) noexcept = default;
    Scene& operator = (Scene&&) noexcept = default;

protected:
    using Objects = std::unordered_map<IDGenerator::ID, GameObject*>;

protected:
    Objects m_Objects{};
};
