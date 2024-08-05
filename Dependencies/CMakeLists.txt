target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(GLFW)
add_subdirectory(GLEW)
add_subdirectory(OpenGL)
add_subdirectory(GML)


# add_subdirectory(STB)
