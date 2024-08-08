target_sources(${PROJECT_NAME}
    PRIVATE Main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Shader)
add_subdirectory(GPUProgram)
add_subdirectory(Boundable)
add_subdirectory(Buffer)
add_subdirectory(VertexArray)
add_subdirectory(Texture)
add_subdirectory(AttributePointer)

add_subdirectory(FileReader)
add_subdirectory(TextureSpawn)
