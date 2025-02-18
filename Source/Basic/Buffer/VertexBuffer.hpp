#pragma once

#include "Buffer.hpp"

#include <GL/glew.h>
#include <GML/Vector/Definitions.hpp>

using VertexType = float;

using Vertex2DBuffer = Buffer<GML::Vec2f, GL_ARRAY_BUFFER>;
