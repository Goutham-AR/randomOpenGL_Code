cmake_minimum_required(VERSION 3.7)

if(${CMAKE_VERSION} VERSION_LESS 3.20)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.20)
endif()

project(
    OpenGL
    VERSION 0.1.0
    DESCRIPTION "random opengl programs"
    LANGUAGES C CXX)

add_subdirectory(external/stb_image)
add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(src)

