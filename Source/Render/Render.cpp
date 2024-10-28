#include "Render.hpp"

#include <cassert>

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

void Render::Draw(const std::size_t count) noexcept
{
     glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

NRenderSpaceEnd
