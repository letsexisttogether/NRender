#include <cmath>
#include <cstdint>
#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "STB/stb_image.h"

#include "Buffer/VertexBuffer.hpp"
#include "FileReader/FileReader.hpp"
#include "VertexArray/VertexArray.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Shaders/Shader.hpp"
#include "Texture/Texture.hpp"
#include "TextureSpawn/TextureSpawner.hpp"

std::int32_t main(std::int32_t argc, char** argv)
{
    if (!glfwInit())
    {
        std::cerr << "Can't initialize GLFW" << std::endl;

        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 600, "CloseGH",
        nullptr, nullptr);

    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;

        return EXIT_FAILURE;
    }

    const TextureSpawner::TexturePath texturesPath
    {
        "D:/Projects/OPPL/Textures/"
    };

    TextureSpawner spawner{ TexFillParams{}, GL_TEXTURE0 };
    
    Texture firstTexture{ spawner.LoadTexture(texturesPath + argv[1]) };

    Texture secondTexture{ spawner.LoadTexture(texturesPath + argv[2]) };

    std::cout << "Hello, CloseGH again" << std::endl;

    FileReader reader{};

    const std::string shadersPath
    {
        "D:/Projects/OPPL/Shaders/"
    };

    VertexArray firstTriangle{};
    firstTriangle.Bind();

    VertexBuffer firstVertecies 
    { 
        {
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f,
        }
    };
    firstVertecies.Bind();
    firstVertecies.FillData();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader firstVertexShader
    {
        GL_VERTEX_SHADER,
        reader.Read(shadersPath + "Default.vert")
    };
    Shader firstFragmenShader 
    {
        GL_FRAGMENT_SHADER,
        reader.Read(shadersPath + "Default.frag")
    };

    firstVertexShader.Compile();
    firstFragmenShader.Compile();

    GPUProgram firstProgram 
    { 
        std::move(firstVertexShader),
        std::move(firstFragmenShader)
    };
    firstProgram.Link();

    while (!glfwWindowShouldClose(window))
    {
        // glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        const Boundable::BoundableID programID = firstProgram.GetID();
        const Boundable::BoundableID uniformLocation = 
            glGetUniformLocation(programID, "offset");

        const float timeValue = glfwGetTime();
        const float offset = (std::sin(timeValue));

        firstProgram.Bind();
        glUniform3f(uniformLocation, offset, 0.0f, 0.0f);


        const std::int32_t firstTextureLocation =
            glGetUniformLocation(firstProgram.GetID(), "texture1");
        const std::int32_t secondTextureLocation =
            glGetUniformLocation(firstProgram.GetID(), "texture2");

        glUniform1i(firstTextureLocation, firstTexture.GetSlot() 
            - GL_TEXTURE0);
        glUniform1i(secondTextureLocation, secondTexture.GetSlot() 
            - GL_TEXTURE0);

        firstTexture.Bind();
        secondTexture.Bind();

        firstTriangle.Bind();
        glDrawArrays(GL_TRIANGLES, 0, firstVertecies.GetCount());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}
