#pragma once

#include <GML/Vector/Definitions.hpp>

#include "Boundable/Boundable.hpp"
#include "Drawable/Drawable.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Primitive/Base/Rectangle/Rectangle.hpp"

class Camera : Rectangle, public Drawable
{

public: 
    Camera() = delete;
    Camera(const Camera&) = default;
    Camera(Camera&&) = default;

    // TODO: remove program, create a global OpenGL context with GPUprogram
    Camera(const Position origin, const Size width, const Size height,
        GPUProgram& program);

    ~Camera() = default;

    // Later move the interface to a dedicated class Transformable 
    void Move(const Vec2f moveBy) noexcept; 

    void Draw() noexcept override;


private:
    GPUProgram& m_Program;
};
