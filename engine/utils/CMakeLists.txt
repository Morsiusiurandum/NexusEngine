file(GLOB_RECURSE src *.h *.cpp)

add_library(utils SHARED ${src})

set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(utils PROPERTIES CLEAN_DIRECT_OUTPUT 1)



