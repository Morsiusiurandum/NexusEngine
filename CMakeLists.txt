# Edit the BuildOptions.cmake file to change build time options
include(BuildOptions.cmake)

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

project(${MAIN_PROJECT_NAME} LANGUAGES CXX)

# load package
find_package(directxtex CONFIG REQUIRED)

# compile libs
add_subdirectory(utils)

# compile shaders
add_subdirectory(shader)

# compile exe
add_subdirectory(app)

# sort compile
add_dependencies(${MAIN_PROJECT_NAME} utils)
add_dependencies(${MAIN_PROJECT_NAME} shaders)

target_link_libraries(${MAIN_PROJECT_NAME} PRIVATE utils)

# define macros
if (ENABLE_NOTIFICATION_ICON)
    add_compile_definitions(_ENABLE_NOTIFICATION_ICON)
endif ()

if (SINGLE_INSTANCE_ONLY)
    add_compile_definitions(_SINGLE_INSTANCE_ONLY)
endif ()

