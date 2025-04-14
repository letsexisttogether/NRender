#include "Test.hpp"

#include <array>
#include <fstream>
#include <utility>


#include "Core/Core.hpp"
#include "Texture/Texture.hpp"
#include "Utility/Convert/GetGLType.hpp"

Player::Player(InstanceSource<ColorVertex, ComplexVertex>& instanceSource,
    const std::uint32_t instanceID) noexcept
    : m_InstanceSource{ instanceSource }, m_InstanceID{ instanceID }
{}

void Player::Move(const GML::Vec2f distance) noexcept
{
    auto instance = m_InstanceSource.GetInstance(m_InstanceID);

    instance.Position.X() += distance.X();
    instance.Position.Y() += distance.Y();

    m_InstanceSource.SetInstance(m_InstanceID, std::move(instance));
}

VertexArrayObject CreateSeparateVAO() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<GML::Vec2f> positions
    {
        { -0.5f,  0.5f },
        { 0.5f, -0.5f },
        { -0.5f, -0.5f },

        { -0.5f,  0.5f }, 
        { 0.5f, -0.5f },
        { 0.5f,  0.5f }
    };

    VertexBufferObject positionVBO{ true };
    positionVBO.SetData(positions, GL_STATIC_DRAW);

    VertexAttribPointer positionVAP
    {
        0, 2, GetGLType<GML::Vec2f>(), false, sizeof(GML::Vec3f), 0
    };

    const std::vector<GML::Vec3f> colors
    {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f },

        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 1.0f }
    };

    VertexBufferObject colorVBO{ true };
    colorVBO.SetData(colors, GL_STATIC_DRAW); 

    VertexAttribPointer colorVAP
    {
        1, 3, GetGLType<GML::Vec3f>(), false, sizeof(GML::Vec3f), 0
    };

    VAO.Unbind();

    return VAO;
}

VertexArrayObject CreateInstancedVAO() noexcept
{
    VertexArrayObject VAO{ true };

    VertexBufferObject baseVBO{ true };

    const std::vector<float> vertices
    {
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,   
        0.05f,  0.05f,  0.0f, 1.0f, 1.0f	
    };

    baseVBO.SetData(vertices, GL_STATIC_DRAW);

    VertexAttribPointer vap0
    {
        0, 2, GetGLType<float>(), false, 5 * sizeof(float), 0
    };
    
    VertexAttribPointer vap1
    {
        1, 3, GetGLType<float>(), false, 5 * sizeof(float), 2 * sizeof(float)
    };

    VertexBufferObject instancedVBO{ true };

    std::vector<GML::Vec2f> instances{ CreateInstances() };

    VertexAttribPointer vap2
    {
        2, 2, GetGLType<GML::Vec2f>(), false, sizeof(GML::Vec2f), 0
    };
    vap2.SetDivisor(1);

    instancedVBO.SetData(instances, GL_STATIC_DRAW);

    VAO.Unbind();

    return VAO;
}

VertexArrayObject CreateVAOColorVertex() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<ColorVertex> vertices
    {
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },   
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f } }
    };
    
    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(vertices, GL_STATIC_DRAW);

    VertexLayout<ColorVertex>::SpawnAttributes();

    VAO.Unbind();

    return VAO;
}

VertexArrayObject CreateScaledInstance() noexcept
{
    VertexArrayObject VAO{ true };

    const std::vector<ColorVertex> baseData
    {
        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f },   { 0.0f, 0.0f, 1.0f } },

        { { -0.5f,  0.5f },   { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f },    { 0.0f, 1.0f, 0.0f } },   
        { { 0.5f,  0.5f },    { 0.0f, 1.0f, 1.0f } }
    };

    VertexBufferObject baseVBO{ true };
    baseVBO.SetData(baseData, GL_STATIC_DRAW);

    auto baseAttributes = VertexLayout<ColorVertex>::SpawnAttributes();

    const std::vector<ComplexVertex> instancesData
    {
        { { 0.0f,  0.5f },  0.5f },
        { { 0.0f, -0.5f },  0.5f },
        { { 0.5f, 0.0f },   0.5f },
        { { -0.5f, 0.0f },  0.5f },
    };

    VertexBufferObject instancesVBO{ true };
    instancesVBO.SetData(instancesData, GL_STATIC_DRAW);

    auto attributes = VertexLayout<ComplexVertex>::SpawnAttributes(2);

    for (auto& attribute : attributes)
    {
        attribute.SetDivisor(1);
    }

    VAO.Unbind();

    return VAO;
};

std::vector<GML::Vec2f> CreateInstances() noexcept
{
    std::vector<GML::Vec2f> offsets{};
    offsets.reserve(100);

    const float shift = 0.1f;

    for (std::int32_t y = -10; y < 10; y += 2)
    {
        for (std::int32_t x = -10; x < 10; x += 2)
        {
            GML::Vec2f offset
            {
                static_cast<float>(x) / 10.0f + shift,
                static_cast<float>(y) / 10.0f + shift
            };

            offsets.push_back(std::move(offset));
        }
    }
    
    return offsets;
}


GPUProgram CreateModernGPUProgram() noexcept
{
    Shader vertexShader{ GL_VERTEX_SHADER, "shader.vert" };
    Shader fragmentShader{ GL_FRAGMENT_SHADER, "shader.frag" };

    GPUProgram gpuProgram
    { 
        std::move(vertexShader),
        std::move(fragmentShader),
        false
    };

    return gpuProgram;
}

/*
std::uint32_t CreateTexture() noexcept
{
    constexpr GLenum textureType = GL_TEXTURE_2D;

    std::uint32_t textureID{};
    glGenTextures(1, &textureID);
    glBindTexture(textureType, textureID);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    constexpr std::array<float, 4> borderColor
    {
        1.0f, 1.0f, 0.0f, 1.0f
    };
    glTexParameterfv(textureType, GL_TEXTURE_BORDER_COLOR, borderColor.data());

    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::int32_t width{};
    std::int32_t height{};
    std::int32_t nrChannels{};

    // Flip the texture
    stbi_set_flip_vertically_on_load(true);  

    std::uint8_t* textureRawData = stbi_load("container.jpg", &width, &height,
        &nrChannels, 0);

    assert(textureRawData && "The data was not loaded properly");

    glTexImage2D(textureType, 0, GL_RGB, width, height, 0, GL_RGB,
        GetGLType<std::uint8_t>(), textureRawData);

    stbi_image_free(textureRawData);

    return textureID;
}
*/

Texture CreateModernTexture() noexcept
{
    const std::filesystem::path path{ "container.jpg" };

    Texture texture{ path, GL_TEXTURE0, GL_TEXTURE_2D, {} };
    texture.Unbind();

    return texture;
}

std::uint32_t CreateGPUProgram() noexcept
{
    const std::uint32_t gpuProgram = glCreateProgram();

    const auto vertexShaderSource = ReadShader("shader.vert");
    const char* vertexShaderData = vertexShaderSource.data();

    const std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderData, nullptr);
    glCompileShader(vertexShader);

    const auto fragmentShaderSource = ReadShader("shader.frag");
    const char* fragmentShaderData = fragmentShaderSource.data();

    const std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderData, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(gpuProgram, vertexShader);
    glAttachShader(gpuProgram, fragmentShader);

    glLinkProgram(gpuProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return gpuProgram;
}

std::vector<char> ReadShader(const std::string& fileName) noexcept
{
    assert(std::filesystem::exists(fileName) && "File does not exist");

    std::vector<char> shader{};

    std::ifstream inputStream{ fileName };

    inputStream.seekg(0, std::ios::end);
    const std::streamsize fileSize = inputStream.tellg();
    inputStream.seekg(0, std::ios::beg);

    shader.resize(fileSize);

    inputStream.read(shader.data(), fileSize);

    return shader;
}

bool IsKeyPressed(NRender::Window& window, const std::int32_t key) noexcept
{
    return glfwGetKey(window.GetBaseWindow(), key) == GLFW_PRESS;
}
