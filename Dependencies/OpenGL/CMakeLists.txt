find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${OPENGL_LIBRARIES})
