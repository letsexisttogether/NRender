#pragma once

#include "Primitive/Primitive.hpp"
#include "Primitive/Base/Rectangle/Rectangle.hpp"

class Square : public Rectangle, public Primitive
{
public:
    Square() = delete;
    Square(const Square&) = delete;
    Square(Square&&) = default;

    Square(const Position origin, const Size size);

    ~Square() = default;

    Square& operator = (const Square&) noexcept = delete;
    Square& operator = (Square&&) noexcept = default;

protected:
    void Generate() noexcept override;
};
