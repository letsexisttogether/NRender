#pragma once

#include <cstdint>

class Resolution
{
public:
    using Dimension = std::int32_t;

public:
    Dimension Width{}; 
    Dimension Height{}; 
};
