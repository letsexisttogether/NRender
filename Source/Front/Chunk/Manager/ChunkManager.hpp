#pragma  once

#include <optional>
#include <unordered_map>

#include "Front/Chunk/Chunk.hpp"
#include "Front/IDGenerator/IDGenerator.hpp"

class ChunkManager 
{
public:
    using Chunks = std::unordered_map<IDGenerator::ID, Chunk>;

public:
    ChunkManager() = default;
    ChunkManager(const ChunkManager&) = default;
    ChunkManager(ChunkManager&&) = default;

    ~ChunkManager() = default;

    void AddChunk(Chunk&& chunk) noexcept;

    void DistributeObject(const IDGenerator::ID id) noexcept;

    const Chunks& GetChunks() const noexcept;
    Chunks& GetChunks() noexcept;

private:
    Chunks m_Chunks{};
        
    IDGenerator m_IDGenerator{};
};
