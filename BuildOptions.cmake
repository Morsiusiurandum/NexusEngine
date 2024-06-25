## Determine which platform is being built
SET(BUILD_PRESENT_NAME_PLATFORM "unknown")

IF (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    SET(BUILD_PRESENT_NAME_PLATFORM "linux")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    SET(BUILD_PRESENT_NAME_PLATFORM "windows")
ELSE ()
    SET(BUILD_PRESENT_NAME_PLATFORM "${CMAKE_HOST_SYSTEM_NAME}")
ENDIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")

## Determine the CPU architecture
SET(BUILD_PRESENT_NAME_ARCHITECTURE "unknown")

IF ("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "x64")
    SET(BUILD_PRESENT_NAME_ARCHITECTURE "x64")
ELSEIF ("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
    SET(BUILD_PRESENT_NAME_ARCHITECTURE "x86")
ENDIF ()

## Determine the build type
SET(BUILD_PRESENT_NAME_BUILD_TYPE "unknown")

## The default is a debug build
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF ()

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(BUILD_PRESENT_NAME_BUILD_TYPE "debug")
ELSE (CMAKE_BUILD_TYPE MATCHES "Release")
    SET(BUILD_PRESENT_NAME_BUILD_TYPE "release")
ENDIF ()

SET(BUILD_PRESENT_NAME ${BUILD_PRESENT_NAME_PLATFORM}-${BUILD_PRESENT_NAME_ARCHITECTURE}-${BUILD_PRESENT_NAME_BUILD_TYPE})

MESSAGE(STATUS "The configuration is detected: ${BUILD_PRESENT_NAME}")

# change this to your preferred name for the entire project
SET(MAIN_PROJECT_NAME "Nexus")

# change this to SET the executable name for the windows application
SET(WINDOWS_APP_NAME "Nexus")

# Set to true to enable the notification icon code
SET(ENABLE_NOTIFICATION_ICON true)

# Set to false to allow multiple instances of the application to run
# simultaneously.  Otherwise an error will display when trying to run more than one.
SET(SINGLE_INSTANCE_ONLY true)

SET(CMAKE_MINIMUM_REQUIRED_VERSION 3.24)


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/${BUILD_PRESENT_NAME})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/${BUILD_PRESENT_NAME})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
