#pragma once

#include <vector>
#include <GML/Vector/Definitions.hpp>

#include "Texture/Texture.hpp"
#include "Window/Window.hpp"
#include "VAO/VertexArrayObject.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Buffer/Buffer.hpp"
#include "VAP/VertexAttribPointer.hpp"
#include "Vertex/ColorVertex.hpp"
#include "Vertex/ComplexVertex.hpp"
#include "Instance/InstanceSource.hpp"

class Player
{
public:
    Player() = delete;
    Player(const Player&) = delete;
    Player(Player&&) = default;

    Player(InstanceSource<ColorVertex, ComplexVertex>& instanceSource,
        const std::uint32_t instanceID) noexcept;

    ~Player() = default;

    void Move(const GML::Vec2f distance) noexcept;
    
    Player& operator = (const Player&) = delete;
    Player& operator = (Player&&) = delete;

private:
    InstanceSource<ColorVertex, ComplexVertex>& m_InstanceSource;
    std::uint32_t m_InstanceID;
};

VertexArrayObject CreateSeparateVAO() noexcept;
VertexArrayObject CreateInstancedVAO() noexcept;
VertexArrayObject CreateVAOColorVertex() noexcept;

VertexArrayObject CreateScaledInstance() noexcept;

std::vector<GML::Vec2f> CreateInstances() noexcept;

GPUProgram CreateModernGPUProgram() noexcept;

// std::uint32_t CreateTexture() noexcept;
Texture CreateModernTexture() noexcept;

// About to remove
std::uint32_t CreateGPUProgram() noexcept;
std::vector<char> ReadShader(const std::string& fileName) noexcept;


// Utility
bool IsKeyPressed(NRender::Window& window, const std::int32_t key) noexcept;

