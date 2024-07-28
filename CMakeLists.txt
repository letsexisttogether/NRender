cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(CloseGH LANGUAGES CXX)

add_executable(${PROJECT_NAME})

add_subdirectory(Source)
add_subdirectory(Dependencies)

