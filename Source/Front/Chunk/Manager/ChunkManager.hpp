#pragma  once

#include <unordered_set>

#include "Front/Chunk/Chunk.hpp"

class ChunkManager 
{
public:
    using Chunks = std::unordered_set<Chunk, Chunk::Hash, Chunk::Equal>;

public:
    ChunkManager() = default;
    ChunkManager(const ChunkManager&) = default;
    ChunkManager(ChunkManager&&) = default;

    ~ChunkManager() = default;

    void AddChunk(Chunk&& chunk) noexcept;

    void DistributeObject(const IDable::ID id) noexcept;

private:
    Chunks m_Chunks{};
};
