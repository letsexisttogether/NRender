#include "VertexAttribPointer.hpp"

VertexAttribPointer::VertexAttribPointer(const std::uint32_t location,
    const Size size, const GLenum type, const bool shouldNormalize,
    const Size stride, const Size offset)
    : m_Size{ size }, m_Type{ type },
    m_ShouldNormalize{ shouldNormalize }, m_Stride{ stride },
    m_Offset{ reinterpret_cast<void*>(offset) }
{
    m_ID = location;

    Init(true);
}

void VertexAttribPointer::Bind() noexcept
{
    glEnableVertexAttribArray(m_ID);
}

void VertexAttribPointer::Unbind() noexcept
{
    glDisableVertexAttribArray(m_ID);
}

void VertexAttribPointer::SetDivisor(const Size divisor) noexcept
{
    glVertexAttribDivisor(m_ID, divisor);
}

void VertexAttribPointer::Generate() noexcept
{
    glVertexAttribPointer(m_ID, m_Size, m_Type, m_ShouldNormalize,
        m_Stride, m_Offset);
}
