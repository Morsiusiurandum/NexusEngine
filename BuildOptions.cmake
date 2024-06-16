# The vcpkg toolchain is in %VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake,
# where %VCPKG_ROOT% is your vcpkg installation path.
set(CMAKE_TOOLCHAIN_FILE C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# change this to your preferred name for the entire project
set(MAIN_PROJECT_NAME "Nexus")

# change this to set the executable name for the windows application
set(WINDOWS_APP_NAME "Nexus")

# Set to true to enable the notification icon code
set(ENABLE_NOTIFICATION_ICON true)

# Set to false to allow multiple instances of the application to run
# simultaneously.  Otherwise an error will display when trying to run more than one.
set(SINGLE_INSTANCE_ONLY true)

set(CMAKE_MINIMUM_REQUIRED_VERSION 3.24)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()