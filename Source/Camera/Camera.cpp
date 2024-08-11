#include "Camera.hpp"
#include "GML/Matrix/Definitions.hpp"
#include "GML/Variations/Transformation.hpp"
#include "Primitive/Base/Rectangle/Rectangle.hpp"

#include <GML/Variations/Projection.hpp>

Camera::Camera(const Position origin, const Size width, const Size height,
    GPUProgram& program)
    : Rectangle{ origin, width, height }, m_Program{ program }
{}

void Camera::Move(const Vec2f moveBy) noexcept
{
    const Mat4x4f translate
    { 
        GetTranslation(Vec3f{ moveBy.X(), moveBy.Y(), 0.0f }) 
    };

    m_Program.SetUniform("translate", translate);
}

void Camera::Draw() noexcept
{
    const Vec2f leftBottom{ GetLeftBottom() };
    const Vec2f rightTop{ GetRightTop() };

    const Mat4x4f projection
    { 
        GetOrthogonal(leftBottom.X(), rightTop.X(),
            leftBottom.Y(), rightTop.Y(), 0.0f, 1.0f) 
    }; 

    m_Program.SetUniform("projection", projection);
}
