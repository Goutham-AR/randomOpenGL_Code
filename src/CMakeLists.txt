add_executable(
    opengl
    main.cpp
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

)

# target_link_directories(
#     opengl
#     PUBLIC 
#         ${PROJECT_SOURCE_DIR}/build/external/glfw/src
#         ${PROJECT_SOURCE_DIR}/build/external/glad
        
# )


target_link_libraries(
    opengl
    PUBLIC
        glfw
        glad
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
