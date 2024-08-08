#pragma once

#include "Buffer.hpp"

#include <GLEW/glew.h>

using IndexBuffer = Buffer<std::uint32_t, GL_ELEMENT_ARRAY_BUFFER>;
