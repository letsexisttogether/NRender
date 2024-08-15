#pragma once

#include <GML/Vector/Definitions.hpp>

#include "Basic/GPUProgram/GPUProgram.hpp"
#include "Front/Drawable/Drawable.hpp"
#include "Front/Primitive/Base/Rectangle/Rectangle.hpp"

class Camera : public Rectangle, public Drawable
{
public: 
    Camera() = delete;
    Camera(const Camera&) = default;
    Camera(Camera&&) = default;

    // TODO: remove program, create a global OpenGL context with GPUprogram
    Camera(const Rectangle& rectangle, GPUProgram& program);

    ~Camera() = default;

    void Draw() noexcept override;

    Camera& operator = (const Camera&) noexcept = delete;
    Camera& operator = (Camera&&) noexcept = delete;

private:
    void CalculateProjection() noexcept;

private:
    GPUProgram& m_Program;

    GML::Mat4x4f m_Projection{};

    // For the later enhancements
    // GML::Mat4x4f m_View{};
};
