cmake_minimum_required(VERSION 3.10)
project(im-backend LANGUAGES C)

# Enable the compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "DEBUG")

# Set the Windows SDK includes and libs
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0)
set(CMAKE_SYSTEM_PROCESSOR x86)
set(CMAKE_WINDOWS_SDK_VERSION 10.0)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message(STATUS "MSVC_VERSION = ${MSVC_VERSION}")
  message(STATUS "MSVC_TOOLSET_VERSION = ${MSVC_TOOLSET_VERSION}")
endif()

# Add the necessary libraries
include_directories(${PROJECT_SOURCE_DIR}/include $ENV{WindowsSDKDir}/Include/um/x86 $ENV{WindowsSDKDir}/Include/um/x64)
# link_directories($ENV{LIB})
find_library(USER32_LIB user32)
if(USER32_LIB)
  message("Found user32 library: ${USER32_LIB}")
else()
  message(FATAL_ERROR "Could not find user32 library")
endif()

find_library(IMM32_LIB IMM32)
if(IMM32_LIB)
  message("Found user32 library: ${IMM32_LIB}")
else()
  message(FATAL_ERROR "Could not find user32 library")
endif()

# Add the source files recursively
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TESTS ${PROJECT_SOURCE_DIR}/test/*.c ${PROJECT_SOURCE_DIR}/test/*.cpp)


# Add the sources to the library
add_library(im-backend MODULE ${SOURCES})
add_executable(im-test WIN32 ${TESTS} ${SOURCES})

# Link against the necessary libraries
target_link_libraries(im-backend ${USER32_LIB} ${IMM32_LIB})
target_link_libraries(im-test ${USER32_LIB} ${IMM32_LIB})
target_link_options(im-test PRIVATE "/SUBSYSTEM:console")

# Set the output file name
set_target_properties(im-backend PROPERTIES OUTPUT_NAME "im-backend")
set_target_properties(im-test PROPERTIES OUTPUT_NAME "im-test")