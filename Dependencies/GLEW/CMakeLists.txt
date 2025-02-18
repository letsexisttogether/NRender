include(FetchContent)

set(CD ${CMAKE_BINARY_DIR}/_deps/glew-src)

FetchContent_Declare(
    GLEW
    URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip
)

FetchContent_MakeAvailable(GLEW)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CD}/include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${CD}/lib/Release/x64/glew32s.lib)
