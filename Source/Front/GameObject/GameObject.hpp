#pragma once

#include "Front/Drawable/Drawable.hpp"

class GameObject : public Drawable
{
public:
    GameObject() = default;
    GameObject(const GameObject&) = default;
    GameObject(GameObject&&) = default;

    virtual ~GameObject() = default;

    void Draw() noexcept override;

    GameObject& operator = (const GameObject&) noexcept = default;
    GameObject& operator = (GameObject&&) noexcept = default;
};
