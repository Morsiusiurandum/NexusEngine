# Edit the BuildOptions.cmake file to change build time options
include(BuildOptions.cmake)

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

project(${MAIN_PROJECT_NAME})

add_subdirectory(app)
add_subdirectory(shader)

if (ENABLE_NOTIFICATION_ICON)
    add_compile_definitions(_ENABLE_NOTIFICATION_ICON)
endif ()

if (SINGLE_INSTANCE_ONLY)
    add_compile_definitions(_SINGLE_INSTANCE_ONLY)
endif ()

add_dependencies(${MAIN_PROJECT_NAME} shaders)