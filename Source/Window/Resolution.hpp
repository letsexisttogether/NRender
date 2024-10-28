#pragma once

#include <cstdint>

#include "Utility/Namespace.hpp"

NRenderSpaceStart

class Resolution
{
public:
    using Dimension = std::int32_t;

public:
    Dimension Width{}; 
    Dimension Height{}; 
};

NRenderSpaceEnd
