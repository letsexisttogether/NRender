#pragma once

#include <vector>
#include <GML/Vector/Definitions.hpp>

#include "Experimental/VAO/VertexArrayObject.hpp"
#include "Experimental/GPUProgram/GPUProgram.hpp"
#include "Experimental/Buffer/Buffer.hpp"
#include "Experimental/VAP/VertexAttribPointer.hpp"
#include "Experimental/Vertex/ColorVertex.hpp"
#include "Experimental/Vertex/ComplexVertex.hpp"

VertexArrayObject CreateSeparateVAO() noexcept;
VertexArrayObject CreateInstancedVAO() noexcept;
VertexArrayObject CreateVAOColorVertex() noexcept;

VertexArrayObject CreateScaledInstance() noexcept;

std::vector<GML::Vec2f> CreateInstances() noexcept;

GPUProgram CreateModernGPUProgram() noexcept;
std::uint32_t CreateGPUProgram() noexcept;

std::vector<char> ReadShader(const std::string& fileName) noexcept;

