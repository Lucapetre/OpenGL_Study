cmake_minimum_required(VERSION 4.0)
project(OpenGL_Study)
set(CMAKE_CXX_STANDARD 20)

# libraries

# stb_image
add_library(stb_image
        libraries/stb_image/stb_image.cpp
)

# glfw
add_subdirectory(libraries/glfw-3.4)

# glad
add_library(glad
        libraries/glad/src/glad.c
)

target_include_directories(glad
        PRIVATE libraries/glad/include/
)

# main program
add_executable(OpenGL_Study
        src/Main.cpp
        src/Shader.h
)

target_link_libraries(OpenGL_Study
        glfw
        glad
        stb_image
)

target_include_directories(OpenGL_Study
        PRIVATE libraries/glfw-3.4/include/GLFW
        PRIVATE libraries/glad/include/glad/
        PRIVATE libraries/glad/include/KHR/
        PRIVATE libraries/stb_image/
)

