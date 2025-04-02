#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>

#include <GML/Vector/Definitions.hpp>

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
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } }
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

    Texture texture{ CreateModernTexture() };
    texture.Bind();

    /*
    InstanceManager manager{};

    const std::int32_t id = manager.AddInstance(std::move(instanceSource));
    auto& aquiredInstance = manager.GetInstance<ColorVertex, ComplexVertex>(id);
    */

    /*
    const std::uint32_t gpuProgram = CreateGPUProgram();
    glUseProgram(gpuProgram);
    */

    Player player{ instanceSource, 3 };

    GPUProgram gpuProgram{ CreateModernGPUProgram() };
    gpuProgram.Bind();

    float previousTime = glfwGetTime();

    while (!window.ShouldClose())
    {
        const float time = glfwGetTime();

        const float deltaTime = (time - previousTime);
        previousTime = time;

        glClear(GL_COLOR_BUFFER_BIT);

        instanceSource.GetVAO().Bind();

        glDrawArraysInstanced(GL_TRIANGLES, 0,
            instanceSource.GetBaseSize(), instanceSource.GetInstancesSize());

        const float speedUp = ((IsKeyPressed(window, GLFW_KEY_LEFT_SHIFT) ?
            (0.4f) : (0.0f)));

        const float distance = (0.1f + speedUp) * deltaTime;

        if (IsKeyPressed(window, GLFW_KEY_W))
        {
            player.Move(GML::Vec2f{ 0.0f, distance });
        }
        else if (IsKeyPressed(window, GLFW_KEY_S))
        {
            player.Move(GML::Vec2f{ 0.0f, -distance });
        }
        if (IsKeyPressed(window, GLFW_KEY_D))
        {
            player.Move(GML::Vec2f{ distance, 0.0f });
        }
        else if (IsKeyPressed(window, GLFW_KEY_A))
        {
            player.Move(GML::Vec2f{ -distance, 0.0f });
        }
        
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

