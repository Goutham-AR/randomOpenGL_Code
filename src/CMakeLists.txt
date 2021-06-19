add_executable(
    opengl
    main.cpp
    glad.c
)

set_target_properties(
    opengl
    PROPERTIES
    CXX_STANDARD 17
)

target_include_directories(
    opengl
    PUBLIC
    ../libs/glad/include
    ${PROJECT_SOURCE_DIR}/external/glfw/include
)

target_link_directories(
    opengl
    PUBLIC ${PROJECT_SOURCE_DIR}/build/external/glfw/src
)


target_link_libraries(
    opengl
    PUBLIC
    glfw3
    dl      # linux only
    GL      # linux only
    X11     # linux only
    pthread # linux only
)
