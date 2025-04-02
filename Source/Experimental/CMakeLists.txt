add_subdirectory(GPUProgram)
add_subdirectory(Texture)
add_subdirectory(Utility)

set (CD ${CMAKE_CURRENT_SOURCE_DIR})

set (EXP_SOURCES 
    ${CD}/Boundable/Boundable.cpp
    ${CD}/VAO/VertexArrayObject.cpp
    ${CD}/Buffer/Buffer.cpp
    ${CD}/VAP/VertexAttribPointer.cpp
    ${CD}/Test/Test.cpp

    ${GPU_PROGRAM_SOURCES}
    ${TEXTURE_SOURCE}
    ${UTILITY_SOURCES}

    PARENT_SCOPE
)
