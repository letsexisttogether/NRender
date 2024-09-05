#include "Render.hpp"

#include <cassert>

void Render::Init() noexcept
{
    assert(!s_IsInit && "It's possible to only initiazlize Render once");

    InitGLEW();
}

void Render::InitGLEW() noexcept
{
    assert(glewInit() == GLEW_OK && "Failed to initialize GLEW");
}
