cmake_minimum_required(VERSION 3.11-3.18)


file( GLOB APP_SOURCES "${CMAKE_SOURCE_DIR}/apps/*.cpp" )

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory ${PROJECT_BINARY_DIR} ezahf_èGEZF8I76z"
    )



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

    add_dependencies(${APP_NAME} copy_resources)

    target_link_libraries(${APP_NAME} learnopengl)

    target_compile_features(${APP_NAME} PUBLIC cxx_std_20)
endforeach( APP_SOURCE ${APP_SOURCES} )

