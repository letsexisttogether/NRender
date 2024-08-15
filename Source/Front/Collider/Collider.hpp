#pragma once

#include "Front/Primitive/Base/Rectangle/Rectangle.hpp"

class Collider
{
public:
    static bool IsCollision(const Rectangle& first, const Rectangle& second)
        noexcept;
};
