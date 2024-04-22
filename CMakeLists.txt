cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0048 NEW)
project(opengles-workspace)
enable_testing()
include(CTest)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)
add_subdirectory(third_party/glm)
# add_subdirectory(third_party/freeglut-3.4)
# add_subdirectory(third_party/freetype-2.13)
add_subdirectory(third_party/googletest-1.14)
add_subdirectory(gtests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

add_library(opengles-workspace_lib STATIC 
    src/Shapes.cpp
    src/RotateShapes.cpp
    src/Table.cpp
    src/glfw_application.cpp
    src/main_loop.cpp
    src/renderer.cpp
    src/input.cpp
    third_party/glad/GL/src/gl.c
    )

include_directories(opengles-workspace_lib PUBLIC
    include
    third_party/glad/GL/include
    third_party/glfw/include
    third_party/googletest-1.14/googletest/include
    third_party/googletest-1.14/googlemock/include
    third_party/glm
    third_party/freeglut-3.4/include
    third_party/freetype-2.13/include
    home/daniel/Desktop/opengles-workspace
    )

add_executable(opengles-workspace 
    main.cpp
)

target_link_libraries(opengles-workspace opengles-workspace_lib glfw ${GLFW_LIBRARIES})