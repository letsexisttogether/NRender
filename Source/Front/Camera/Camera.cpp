#include "Camera.hpp"

#include <GML/Variations/Transformation.hpp>
#include <GML/Variations/Projection.hpp>

Camera::Camera(const Position origin, const Size width, const Size height,
    GPUProgram& program)
    : Rectangle{ origin, width, height }, m_Program{ program }
{}

void Camera::Move(const Position moveBy) noexcept
{
    const GML::Mat4x4f translate
    { 
        GML::GetTranslation(GML::Vec3f{ moveBy.X(), moveBy.Y(), 0.0f }) 
    };

    m_Program.SetUniform("translate", translate);
}

void Camera::Draw() noexcept
{
    const GML::Vec2f leftBottom{ GetLeftBottom() };
    const GML::Vec2f rightTop{ GetRightTop() };

    const GML::Mat4x4f projection
    { 
        GML::GetOrthogonal(leftBottom.X(), rightTop.X(),
            leftBottom.Y(), rightTop.Y(), 0.0f, 1.0f) 
    }; 

    m_Program.SetUniform("projection", projection);
}
