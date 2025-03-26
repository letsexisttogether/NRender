#pragma once

#include "Core/Core.hpp"

// NOTE: I want it to be a set of functions and not a class for now
// I may change it in the future, but as for now I like it this way

template <typename _PrimitiveType>
static GLenum GetGLType() noexcept;
