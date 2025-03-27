#include "Render.hpp"

#include <cassert>

#include "Experimental/Sprite/Sprite.hpp"
#include "Experimental/VAO/VertexArrayObject.hpp"

NRenderSpaceStart

void Render::Init() noexcept
{
    assert(!s_IsInit && "It's possible to only initiazlize Render once");

    InitGLEW();
}

void Render::InitGLEW() noexcept
{
    assert(glewInit() == GLEW_OK && "Failed to initialize GLEW");
}


/*
Nice plane. Delete it
void Render::DrawSprite(const ID spriteID) noexcept
{
    auto& sprite = m_Sprites[spriteID];

    sprite.GetVAO().Bind();

    auto& shader = m_Shaders[sprite.GetShaderID()];
    shader.Bind();

    Draw(6);
    // FindSprite by ID
    // Bind VAO
    // Bind Shader
    // Call glDraw(...)
}
*/

NRenderSpaceEnd
