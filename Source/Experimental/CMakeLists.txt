add_subdirectory(GPUProgram)
add_subdirectory(Texture)
add_subdirectory(Utility)

# Temporal play-around thing
add_subdirectory(Test)

set (CD ${CMAKE_CURRENT_SOURCE_DIR})

set (EXP_SOURCES 
    ${CD}/Boundable/Boundable.cpp
    ${CD}/VAO/VertexArrayObject.cpp
    ${CD}/Buffer/Buffer.cpp
    ${CD}/VAP/VertexAttribPointer.cpp

    ${TEST_SOURCES}
    ${GPU_PROGRAM_SOURCES}
    ${TEXTURE_SOURCE}
    ${UTILITY_SOURCES}

    PARENT_SCOPE
)
