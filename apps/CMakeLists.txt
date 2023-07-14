cmake_minimum_required(VERSION 3.11-3.18)


file( GLOB APP_SOURCES "${CMAKE_SOURCE_DIR}/apps/*.cpp" )

foreach( APP_SOURCE ${APP_SOURCES} )
    get_filename_component(APP_NAME ${APP_SOURCE} NAME_WE)

    
    project(${APP_NAME})
    add_executable( ${APP_NAME} ${APP_SOURCE} )

    target_include_directories(${APP_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
    target_include_directories(${APP_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
    target_include_directories(${APP_NAME} PUBLIC ${GLEW_INCLUDE_DIR})

    target_link_libraries(${APP_NAME} ${SDL2_LIBRARIES})
    target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES})
    target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES})

    target_link_libraries(${APP_NAME} learnopengl)

    target_compile_features(${APP_NAME} PUBLIC cxx_std_20)
endforeach( APP_SOURCE ${APP_SOURCES} )

