#include "DividableScene.hpp"
#include "Front/Primitive/Drawable/Rectangle/DrawableRectangle.hpp"

#include <iostream>
#include <utility>

const static float halfWindowWidth = 1400.0f / 2.0f;
const static float halfWindowHeight = 800.0f / 2.0f;

DividableScene::DividableScene()
{
    Chunk left
    { 
        { 
            { -halfWindowWidth, -halfWindowHeight }, 
            { 0.0f, halfWindowHeight } 
        } 
    };
    Chunk right 
    { 
        { 
            { -halfWindowWidth, -halfWindowHeight }, 
            { 0.0f, halfWindowHeight } 
        } 
    };

    m_ChunkManager.AddChunk(std::move(left));
    m_ChunkManager.AddChunk(std::move(right));

    AddObject(new DrawableRectangle
    {
        { { -100.0f, -100.0f }, { 100.0f, 100.0f } },
        { { 0.0f, 0.0f }, { 1.0f, 1.0f } }
    });
}

void DividableScene::AddObject(GameObject* const object) noexcept
{
    const IDGenerator::ID objectID = m_IDGenerator.GetNext();

    m_Objects.insert({ objectID, object });

    m_ChunkManager.DistributeObject(objectID);
}

void DividableScene::UpdateLogic() noexcept
{

}

void DividableScene::UpdateGraphics() noexcept
{
    // For now drawing every chunk
    for (auto& [id, chunk] : m_ChunkManager.GetChunks())
    {
        chunk.Draw();
    }
}
