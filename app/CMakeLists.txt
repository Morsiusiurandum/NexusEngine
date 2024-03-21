enable_language("RC")

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(_UNICODE UNICODE)

# Uncomment the following line to add timeout to wait so that the
# registry handle can be released.  Not really needed and causes
# a very tiny bit of extra CPU to keep checking for exit condition.
#
#add_compile_definitions(_TIDY_TIMEOUT)

include_directories(include)

set(WIN32_RESOURCES resources/WindowsProject.rc)

file(GLOB_RECURSE resources resources/**)
file(GLOB_RECURSE src src/** include/**)

add_executable(${WINDOWS_APP_NAME} WIN32 ${resources} ${src})

set(LIBS d3d11 D3DCompiler)

# link DirectX libs
target_link_libraries(${WINDOWS_APP_NAME} PRIVATE ${LIBS})

# set_target_properties(${WINDOWS_APP_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
# target_link_options(${WINDOWS_APP_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")