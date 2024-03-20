# project(shader)
# Build HLSL shaders
add_custom_target(shaders)

file(GLOB_RECURSE vertex vs/*.hlsl)
file(GLOB_RECURSE pixel ps/*.hlsl)

set(HLSL_VERTEX_SHADER_FILES ${vertex})
set(HLSL_PIXEL_SHADER_FILES ${pixel})

set_source_files_properties(${HLSL_VERTEX_SHADER_FILES} PROPERTIES ShaderType "vs")
set_source_files_properties(${HLSL_PIXEL_SHADER_FILES} PROPERTIES ShaderType "ps")

set(HLSL_SHADER_FILES ${HLSL_VERTEX_SHADER_FILES} ${HLSL_PIXEL_SHADER_FILES})
set_source_files_properties(${HLSL_SHADER_FILES} PROPERTIES ShaderModel "5_0")

set(SHADER_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/shader)
file(MAKE_DIRECTORY ${SHADER_DIRECTORY})

foreach (FILE ${HLSL_SHADER_FILES})
    get_filename_component(FILE_WE ${FILE} NAME_WE)
    get_source_file_property(shadertype ${FILE} ShaderType)
    get_source_file_property(shadermodel ${FILE} ShaderModel)
    add_custom_command(TARGET shaders
            COMMAND fxc.exe /E main /T ${shadertype}_${shadermodel} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo ${SHADER_DIRECTORY}/${FILE_WE}.cso /Fd ${SHADER_DIRECTORY}/${FILE_WE}.pdb ${FILE}
            MAIN_DEPENDENCY ${FILE}
            COMMENT "HLSL ${FILE}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM)
endforeach (FILE)