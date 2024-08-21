#include "Collider.hpp"

#include <cassert>

bool Collider::IsCollision(const Rectangle& first, const Rectangle& second)
    noexcept
{
    const Rectangle::Position firstLB{ first.GetLeftBottom() };
    const Rectangle::Position firstRT{ first.GetRightTop() };

    const Rectangle::Position secondLB{ second.GetLeftBottom() };
    const Rectangle::Position secondRT{ second.GetRightTop() };

    if (firstLB.X() > secondRT.X() || firstRT.X() < secondLB.X())
    {
        return false;
    }

    if (firstLB.Y() > secondRT.Y() || firstRT.Y() < secondLB.Y())
    {
        return false;
    }

    return true;
}
