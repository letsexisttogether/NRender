#include "ChunkManager.hpp"
#include "Front/Collider/Collider.hpp"

#include <utility>

void ChunkManager::AddChunk(Chunk&& chunk) noexcept
{
    m_Chunks.insert(std::move(chunk));
}

void ChunkManager::DistributeObject(const IDable::ID id) noexcept
{
    // This is not the best way to do it


    // This should be 
    // const Object& object = World::GetWorld().GetObject(id);
    const Rectangle object{};

    for (const Chunk& constChunk : m_Chunks)
    {
        Chunk& chunk = const_cast<Chunk&>(constChunk);

        if (Collider::IsCollision(chunk, object))
        {
            chunk.AddObject(id);
        }
    }
}
