#include "Chunk.hpp"

#include <iostream>

#include "Application/Application.hpp"
#include "Front/GameObject/GameObject.hpp"

Chunk::Chunk(const Rectangle& rectangle)
    : Rectangle{ rectangle }
{}

void Chunk::AddObject(const IDGenerator::ID id) noexcept
{
    m_Objects.insert(id);    
}

void Chunk::RemoveObject(const IDGenerator::ID id) noexcept
{
    m_Objects.erase(id);
}

void Chunk::Draw() noexcept
{
    for (const IDGenerator::ID id : m_Objects)
    {
        GameObject* object = Application::GetApp().GetScene()->GetObject(id);

        object->Draw();
    }
}
