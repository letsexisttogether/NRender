#include "Camera.hpp"

#include <GML/Variations/Transformation.hpp>
#include <GML/Variations/Projection.hpp>

Camera::Camera(const Rectangle& rectangle, GPUProgram& program)
    : Rectangle{ rectangle }, m_Program{ program }
{
    CalculateProjection();
}

void Camera::Draw() noexcept
{
    m_Program.SetUniform("projection", m_Projection);
}


void Camera::CalculateProjection() noexcept
{
    m_Projection = GML::GetOrthogonal(m_LeftBottom.X(), m_RightTop.X(),
        m_LeftBottom.Y(), m_RightTop.Y(), 0.0f, 1.0f);
}
