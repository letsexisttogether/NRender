add_subdirectory(Shape)
add_subdirectory(Sprite)
add_subdirectory(Utility)

set (CD ${CMAKE_CURRENT_SOURCE_DIR})

set (EXP_SOURCES 
    ${CD}/Boundable/Boundable.cpp
    ${CD}/VAO/VertexArrayObject.cpp
    ${CD}/Buffer/Buffer.cpp
    
    ${SHAPE_SOURCES}
    ${SPRITE_SOURCES}
    ${UTILITY_SOURCES}

    PARENT_SCOPE
)
