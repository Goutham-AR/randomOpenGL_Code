add_executable(
    opengl
    main.cc
    window.hpp
    window.cc
    shader.hpp
    shader.cc
    input_handler.hpp
)



set_target_properties(
    opengl
    PROPERTIES
    CXX_STANDARD 17
)

target_include_directories(
    opengl
    PUBLIC
        ${PROJECT_SOURCE_DIR}/external/glfw/include
        ${PROJECT_SOURCE_DIR}/external/glad/include
        ${PROJECT_SOURCE_DIR}/external/stb_image/include

)



target_link_libraries(
    opengl
    PUBLIC
        glfw
        glad
        stb_image
)

if(WIN32)
    target_link_libraries(
        opengl
        PUBLIC
            opengl32
    )
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(
        opengl
        PUBLIC
            GL  
            X11 
            pthread 
            dl  
    )
endif()
