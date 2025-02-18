include (FetchContent)

set(CD ${CMAKE_BINARY_DIR}/_deps/STB)

file(DOWNLOAD 
    https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
    ${CD}/stb_image.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CD})
