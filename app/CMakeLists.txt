project(${WINDOWS_APP_NAME})

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(_UNICODE UNICODE)

# Uncomment the following line to add timeout to wait so that the
# registry handle can be released.  Not really needed and causes
# a very tiny bit of extra CPU to keep checking for exit condition.
#
#add_compile_definitions(_TIDY_TIMEOUT)

include_directories(include)

aux_source_directory(resources resources)
file(GLOB_RECURSE src src/*.cpp src/*.h)

add_executable(
        ${PROJECT_NAME}
        ${resources}
        ${src})

set(LIBS d3d11 D3DCompiler)
target_link_libraries(${PROJECT_NAME} ${LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")