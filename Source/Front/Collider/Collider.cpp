#include "Collider.hpp"

#include <cassert>

bool Collider::IsCollision(const Rectangle& first, const Rectangle& second)
    noexcept
{
    static_assert("Implement Collider::IsCollision(Rectangle, Rectangle)");

    const Rectangle::Position firstLeftBottom{ first.GetLeftBottom() };
    const Rectangle::Position firstRightTop{ first.GetRightTop() };

    const Rectangle::Position secondLeftBottom{ second.GetLeftBottom() };
    const Rectangle::Position secondRightTop{ second.GetRightTop() };

    const bool isXCollision = true;   
    const bool isYCollision = true;
    
    return isXCollision && isYCollision;
}
