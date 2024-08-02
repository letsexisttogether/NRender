#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/trigonometric.hpp>

#include "Buffer/VertexBuffer.hpp"
#include "Buffer/IndexBuffer.hpp"
#include "FileReader/FileReader.hpp"
#include "VertexArray/VertexArray.hpp"
#include "GPUProgram/GPUProgram.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "TextureSpawn/TextureSpawner.hpp"
#include "AttributePointer/AttributePointer.hpp"

void ProcessInput(GLFWwindow* window);
void MouseCallBack(GLFWwindow* window, double xpos, double ypos);

const Texture::Resolution windowWidth = 1400;
const Texture::Resolution windowHeight = 800;

glm::vec3 cameraPosition{ 0.0f, 0.0f, 3.0f };
glm::vec3 cameraFront{ 0.0f, 0.0f, -1.0f };
const glm::vec3 cameraUp{ 0.0f, 1.0f, 0.0f };

float yaw{ -90.0f };
float pitch{};

double deltaTime{};
double lastFrameTime{};

float lastX = 400;
float lastY = 300;
bool firstMouse = true;


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

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CloseGH",
        nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

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

    if (argc < 3)
    {
        std::cerr << "The textures' names were not provided" << std::endl;

        return EXIT_FAILURE;
    }
    
    Texture firstTexture{ spawner.LoadTexture(texturesPath + argv[1]) };
    Texture secondTexture{ spawner.LoadTexture(texturesPath + argv[2]) };

    std::cout << "Hello, CloseGH again" << std::endl;

    const FileReader reader{};

    const std::string shadersPath
    {
        "D:/Projects/OPPL/Shaders/"
    };

    VertexArray firstTriangle{};

    VertexBuffer firstVertecies 
    { 
        {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        }
    };

    AttributePointer firstAttribPointer{ 0, 3, GL_FALSE, 5, 0 };
    AttributePointer secondAttribPointer{ 1, 2, GL_FALSE, 5, 3 };

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

    GPUProgram firstProgram 
    { 
        std::move(firstVertexShader),
        std::move(firstFragmenShader)
    };

    const float secondStrength = ((argc > 3) ? (std::atof(argv[3])) : (0.5));

    const std::vector<glm::vec3> cubePositions 
    {
        glm::vec3{ 0.0f, 0.0f, 0.0f }, 
        glm::vec3{ 2.0f, 5.0f, -15.0f }, 
        glm::vec3{ -1.5f, -2.2f, -2.5f },  
        glm::vec3{ -3.8f, -2.0f, -12.3f },  
        glm::vec3{  2.4f, -0.4f, -3.5f },  
        glm::vec3{ -1.7f, 3.0f, -7.5f },  
        glm::vec3{ 1.3f, -2.0f, -2.5f },  
        glm::vec3{ 1.5f, 2.0f, -2.5f }, 
        glm::vec3{ 1.5f, 0.2f, -1.5f }, 
        glm::vec3{ -1.3f, 1.0f, -1.5f }  
    };

    glfwSetCursorPosCallback(window, MouseCallBack);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        const float time = glfwGetTime();
        deltaTime = time - lastFrameTime;
        lastFrameTime = time;

        ProcessInput(window);
        // glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        firstProgram.Bind();

        firstProgram.SetUniform("texture1", firstTexture.GetSlot());
        firstProgram.SetUniform("texture2", secondTexture.GetSlot());
        firstProgram.SetUniform("secondStrength", secondStrength);

        firstTexture.Bind();
        secondTexture.Bind();

        firstTriangle.Bind();

        const glm::mat4 view{ glm::lookAt(cameraPosition, 
            cameraPosition + cameraFront, cameraUp) };
        firstProgram.SetUniform("view", view);

        const glm::mat4 projection{ glm::perspective
            (glm::radians(45.0f), windowWidth / static_cast<float>(windowHeight),
             0.1f, 100.0f) };
        firstProgram.SetUniform("projection", projection);

        const glm::mat4 scale{ glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 1.0f }) };
        firstProgram.SetUniform("scale", scale);


        for (std::uint32_t i = 0; i < 10; ++i) 
        {
            glm::mat4 model
            { 
                glm::translate(glm::mat4{ 1.0f }, cubePositions[i]) 
            };

            const float angle = i * 20.0f;

            model = glm::rotate(model, glm::radians(angle),
                glm::vec3{ 1.0f, 1.0f, 0.5f });

            firstProgram.SetUniform("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    const float cameraSpeed = 2.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp))
            * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp))
            * cameraSpeed;
    }
}

void MouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
    const float sensitivity = 0.1f;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    const float xoffset = (xpos - lastX) * sensitivity;
    const float yoffset = (lastY - ypos) * sensitivity; 

    lastX = xpos;
    lastY = ypos;

    yaw += xoffset;
    pitch += yoffset;

    pitch = std::max(std::min(pitch, 89.0f), -89.0f);

    const glm::vec3 direction
    {
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };

    cameraFront = glm::normalize(direction);
}  
