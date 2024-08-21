#pragma once

#include "Scene/Scene.hpp"
#include "Front/Chunk/Manager/ChunkManager.hpp"

class DividableScene : public Scene
{
public:
    // Just for the development process
    DividableScene();
    DividableScene(const DividableScene&) = default;
    DividableScene(DividableScene&&) = default;

    ~DividableScene() = default;

    void AddObject(GameObject* const object) noexcept override;
    
    void UpdateLogic() noexcept override;
    void UpdateGraphics() noexcept override;

    DividableScene& operator = (const DividableScene&) noexcept = delete;
    DividableScene& operator = (DividableScene&&) noexcept = delete;

private:
    ChunkManager m_ChunkManager{};
    IDGenerator m_IDGenerator{};
};
