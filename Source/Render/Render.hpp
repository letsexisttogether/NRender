#pragma once

#define GLEW_STATIC
#include <GLEW/glew.h>

class Render
{
public:
    static void Init() noexcept;

private:
    static void InitGLEW() noexcept;

private:
    inline static bool s_IsInit{ false };

    /*
        inline static std::unordered_set<Sprite> s_Single{};
        inline static std::unordered_multimap<ID, Batch> s_Batched{};
        inline static std::vector<Instance> s_Instanced{};
    */
};
