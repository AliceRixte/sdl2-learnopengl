cmake_minimum_required(VERSION 3.11-3.18)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

project(main)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(main PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(main PUBLIC ${GLEW_INCLUDE_DIR})

target_link_libraries(main ${SDL2_LIBRARIES})
target_link_libraries(main ${OPENGL_LIBRARIES})
target_link_libraries(main ${GLEW_LIBRARIES})

target_link_libraries(main learnopengl)

target_compile_features(main PUBLIC cxx_std_20)