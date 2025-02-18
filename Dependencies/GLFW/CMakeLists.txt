include(FetchContent)

set(CD ${CMAKE_BINARY_DIR}/_deps/glfw-src)

FetchContent_Declare(
    GLFW
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip 
)

FetchContent_MakeAvailable(GLFW)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CD}/include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${CD}/lib-vc2022/glfw3.lib)
