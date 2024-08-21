#include "ChunkManager.hpp"

#include "Front/Collider/Collider.hpp"

#include <utility>

void ChunkManager::AddChunk(Chunk&& chunk) noexcept
{
    m_Chunks.insert({ m_IDGenerator.GetNext(), std::move(chunk) });
}

void ChunkManager::DistributeObject(const IDGenerator::ID id) noexcept
{
    // This is not the best way to do it

    // This should be
    // const Object& object = World::GetWorld().GetObject(id);
    const Rectangle object{};

    for (auto& [ID, chunk] : m_Chunks)
    {
        if (Collider::IsCollision(chunk, object))
        {
            chunk.AddObject(id);
        }
    }
}

const ChunkManager::Chunks& ChunkManager::GetChunks() const noexcept
{
    return m_Chunks;
}

ChunkManager::Chunks& ChunkManager::GetChunks() noexcept
{
    return m_Chunks;
}
