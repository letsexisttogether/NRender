#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>

#include <GML/Vector/Definitions.hpp>
#include <yvals.h>

#include "Core/Core.hpp"
#include "GLFW/glfw3.h"
#include "Render/Render.hpp"
#include "Window/Window.hpp"

#include "Experimental/Test/Test.hpp"
#include "Experimental/Instance/InstanceSource.hpp"

using namespace NRender;


std::int32_t main(std::int32_t argc, char** argv)
{
    Window window{ "Hello NRender", { 1920, 1080 } };
    Render::Init();

    const std::vector<ColorVertex> baseData
    {
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },   
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f } }
    };

    std::vector<ComplexVertex> instances
    {
        { { 0.0f,  0.5f },  0.5f },
        { { 0.0f, -0.5f },  0.5f },
        { { 0.5f, 0.0f },   0.5f },
        { { -0.5f, 0.0f },  0.5f },
    };

    InstanceSource<ColorVertex, ComplexVertex> instanceSource
    {
        baseData, std::move(instances)
    }; 

    /*
    InstanceManager manager{};

    const std::int32_t id = manager.AddInstance(std::move(instanceSource));
    auto& aquiredInstance = manager.GetInstance<ColorVertex, ComplexVertex>(id);
    */

    /*
    const std::uint32_t gpuProgram = CreateGPUProgram();
    glUseProgram(gpuProgram);
    */

    GPUProgram gpuProgram{ CreateModernGPUProgram() };
    gpuProgram.Bind();

    float animationStart = glfwGetTime();
    float animationMultiplier = 1.0f;

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        if (const float passedTime = time - animationStart;
            passedTime > 2.0f)
        {
            auto instance = instanceSource.GetInstance(3);
            instance.Position.X() += 0.5 * animationMultiplier; 

            instanceSource.SetInstance(3, std::move(instance));

            animationMultiplier = -animationMultiplier;
            animationStart = time;
        }


        glClear(GL_COLOR_BUFFER_BIT);

        instanceSource.GetVAO().Bind();

        glDrawArraysInstanced(GL_TRIANGLES, 0,
            instanceSource.GetBaseSize(), instanceSource.GetInstancesSize());

        /*
        triangles.GetVAO().Bind();
        glDrawArrays(GL_TRIANGLES, 0, triangles.GetVerticesSize());
        */


        window.SwapBuffers();

        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

// nastya 

