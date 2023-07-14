
cmake_minimum_required(VERSION 3.11-3.18)

project(
    SDL2LearnGL
    VERSION 0.1
    DESCRIPTION "I'm learning OpenGL using Joey de Vries's excellent book Learn OpenGL, except I'm using Haskell as a programming language and SDL2 instead of GLFW.")


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(learnopengl)
add_subdirectory(apps)