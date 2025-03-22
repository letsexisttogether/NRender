add_subdirectory(Window)
add_subdirectory(Render)
add_subdirectory(Experimental)

set(PROJECT_SOURCES 
    ${EXP_SOURCES}
    Main.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

