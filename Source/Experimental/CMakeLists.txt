add_subdirectory(GPUProgram)
add_subdirectory(Utility)

set (CD ${CMAKE_CURRENT_SOURCE_DIR})

set (EXP_SOURCES 
    ${CD}/Boundable/Boundable.cpp
    ${CD}/VAO/VertexArrayObject.cpp
    ${CD}/Buffer/Buffer.cpp
    ${CD}/VAP/VertexAttribPointer.cpp

    ${GPU_PROGRAM_SOURCES}
    ${UTILITY_SOURCES}

    PARENT_SCOPE
)
