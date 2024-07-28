#include "Buffer/VertexBuffer.hpp"
#include <iostream>
#include <vector>

#define GLEW_STATIC

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "GPUProgram/GPUProgramCompiler.hpp"
#include "Shaders/ShaderSpawner.hpp"

std::int32_t main()
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

    std::cout << "Hello, CloseGH again" << std::endl;

    const std::vector<float> vertices
    {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,

        -0.2f, -0.2f, 0.0f,
        -0.5, 0.5f, 0.0f,
        0.2, 0.5, 0.0f

    };
    const std::vector<std::uint32_t> indices
    {
        0, 1, 3,
        1, 2, 3
    };

    std::uint32_t vaoID{};
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    std::uint32_t vboID{};
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
        vertices.data(), GL_STATIC_DRAW);

    VertexBuffer vertexBuffer 
    { 
        {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        }
    };

    vertexBuffer.FillData();

    /*
    std::uint32_t eboID{};
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint32_t),
        indices.data(), GL_STATIC_DRAW);
    */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Generate vertex array object
    // Generate some buffer 
    // Bind it to GL_ARRAY_BUFFER
    // Fill GL_ARRAY_BUFFER with data
    // Specify the attribute 
    // Enable the attribute
    // Unbind the buffer 

    ShaderSpawner vertexSpawner
    {
        GL_VERTEX_SHADER,
        {
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0"
        }
    };
    ShaderSpawner fragmentSpawner 
    {
        GL_FRAGMENT_SHADER,
        {
            "#version 330 core\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0f, 0.2f, 0.3f, 1.0f);\n"
            "}\0"
        }
    };

    const GPUPRogramCompiler programCompiler
    { 
        std::move(vertexSpawner),
        std::move(fragmentSpawner)
    };

    const GPUPRogramCompiler::ProgramID programID =
        programCompiler.CompileProgram();

    while (!glfwWindowShouldClose(window))
    {
        // glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);
        glBindVertexArray(vaoID);

        glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.GetCount());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
    
    return EXIT_SUCCESS;
}
