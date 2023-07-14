
cmake_minimum_required(VERSION 3.11-3.18)


project(learnopengl)

add_library(learnopengl src/learnopengl.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(learnopengl PUBLIC cxx_std_20)