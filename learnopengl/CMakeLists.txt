
cmake_minimum_required(VERSION 3.11-3.18)

project(learnopengl)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

message(SOURCES = "${SOURCES}")



add_library(learnopengl ${SOURCES})

target_include_directories(learnopengl PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(learnopengl PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(learnopengl PUBLIC ${GLEW_INCLUDE_DIR})


target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(learnopengl PUBLIC cxx_std_20)