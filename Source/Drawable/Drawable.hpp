#pragma once

// Maybe remove the class later
class Drawable
{
public:
    Drawable() = default;

    virtual ~Drawable() = default;

    virtual void Draw() noexcept = 0;
};
