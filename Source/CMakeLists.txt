add_subdirectory(Window)
add_subdirectory(Render)

add_subdirectory(GPUProgram)
add_subdirectory(Texture)
add_subdirectory(Utility)

# Temporal play-around thing
add_subdirectory(Test)


set (CD ${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES 
    ${CD}/Boundable/Boundable.cpp
    ${CD}/VAO/VertexArrayObject.cpp
    ${CD}/Buffer/Buffer.cpp
    ${CD}/VAP/VertexAttribPointer.cpp

    ${TEST_SOURCES}
    ${GPU_PROGRAM_SOURCES}
    ${TEXTURE_SOURCE}
    ${UTILITY_SOURCES}
    Main.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CD})

