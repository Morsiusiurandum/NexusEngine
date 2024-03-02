cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME ${WINDOWS_APP_NAME})

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(_UNICODE UNICODE)

# Uncomment the following line to add timeout to wait so that the
# registry handle can be released.  Not really needed and causes
# a very tiny bit of extra CPU to keep checking for exit condition.
#
#add_compile_definitions(_TIDY_TIMEOUT)

# Build HLSL shaders
add_custom_target(shaders)

set(HLSL_SHADER_FILES VertexShader.hlsl PixelShader.hlsl)

set_source_files_properties(VertexShader.hlsl PROPERTIES ShaderType "vs")
set_source_files_properties(PixelShader.hlsl PROPERTIES ShaderType "ps")
set_source_files_properties(${HLSL_SHADER_FILES} PROPERTIES ShaderModel "4_0_level_9_3")

foreach(FILE ${HLSL_SHADER_FILES})
    get_filename_component(FILE_WE ${FILE} NAME_WE)
    get_source_file_property(shadertype ${FILE} ShaderType)
    get_source_file_property(shadermodel ${FILE} ShaderModel)
    add_custom_command(TARGET shaders
            COMMAND fxc.exe /nologo /Emain /T${shadertype}_${shadermodel} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo ${CMAKE_BINARY_DIR}/${FILE_WE}.cso /Fd ${CMAKE_BINARY_DIR}/${FILE_WE}.pdb ${FILE}
            MAIN_DEPENDENCY ${FILE}
            COMMENT "HLSL ${FILE}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM)
endforeach(FILE)



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