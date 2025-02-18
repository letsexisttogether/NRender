include(FetchContent)

set(CD ${CMAKE_BINARY_DIR}/_deps/gml-src)

FetchContent_Declare(
    GML
    GIT_REPOSITORY https://github.com/letsexisttogether/GML
)

FetchContent_MakeAvailable(GML)

if(TARGET GML)
    add_library(GML::GML ALIAS GML)
endif()

set (GML_INCLUDE ${CD}/Include/GML)
file(MAKE_DIRECTORY ${GML_INCLUDE})

# I've just deleted everything from Volume D
# I don't wanna be restoring it all again
if(EXISTS ${GML_INCLUDE})
    file(REMOVE_RECURSE ${GML_INCLUDE})
endif()

file(GLOB_RECURSE GML_FILES ${CD}/Source/*)

foreach(FILE ${GML_FILES})
    get_filename_component(EXTENSION ${FILE} EXT)
    
    if(NOT (EXTENSION STREQUAL ".h" OR EXTENSION STREQUAL ".hpp"))
        continue()
    endif()

    file(RELATIVE_PATH REL_PATH "${CD}/Source" "${FILE}")
    get_filename_component(FILE_DIR "${REL_PATH}" DIRECTORY)
    
    file(MAKE_DIRECTORY "${GML_INCLUDE}/${FILE_DIR}")

    file(COPY "${FILE}" DESTINATION "${GML_INCLUDE}/${FILE_DIR}")
endforeach()

target_link_libraries(${PROJECT_NAME} PRIVATE GML::GML)
target_include_directories(${PROJECT_NAME} PRIVATE ${CD}/Include)
