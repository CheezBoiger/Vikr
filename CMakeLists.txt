#
# Vikr Build script for compilation.
# Copyright (c) Mario Garcia, Under the MIT License.
#
cmake_minimum_required(VERSION 2.8)

project("VikrSoftware")

# Checking Operating system version.
if (WIN32)
  message("Windows")
elseif(UNIX)
  message("Linux")
else()
  message(ERROR_FATAL "Operating system not compatible with Vikr!")
  return()
endif()



# Name version
set(VIKR_VERSION "v0.6")
option(vulkan "Build Vikr with Vulkan extension." OFF)
option(debug "debug the software." OFF)
option(build64 "Build the Vikr Library for 64-bit applications" OFF)


# if (vulkan)
#   set(GLFW_VULKAN_STATIC ON)
# else()
#   set(GLFW_VULKAN_STATIC OFF)
# endif()


# Build For GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS    OFF)

# Set the module path for this build
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

add_subdirectory(libs/glfw)

# This may not need to be here.
if (Vulkan_FOUND)
  set(VULKAN_FOUND ON)
endif()

add_subdirectory(libs/assimp)


# Configurations.
include(cmake/configurable.cmake)


if (${CMAKE_CXX_COMPILER_ID})
  # Doing some stuff for organization.
  if (MSVC)
    foreach(source IN LISTS VIKR_GLOB)
      get_filename_component(source_path "${source}" PATH)
      string(REPLACE "/" "\\" source_path_msvc "${source_path}")
      source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
  endif()
endif()


set(VIKR_NAME "${VIKR_NAME}_${VIKR_VERSION}")

link_directories(
                 ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/ 
                 ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/
                 ${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype/lib/
)

# This will have to be changed up a bit though...
# A Rendering engine is usually broken up into pieces, is this ok though?
add_library(
  ${VIKR_NAME} STATIC
  ${VIKR_GLOB}
)

# Version might need to be determined, as well as updating to compensate for static libs on OS's other than windows.

target_link_libraries(${VIKR_NAME} glfw)

if (vulkan AND VULKAN_FOUND)
  target_link_libraries(${VIKR_NAME} ${Vulkan_LIBRARY})
else()
 message("No vulkan libraries were linked.")
endif()

# Version 0.6.1 (0x 00 06 01)
target_compile_definitions(${VIKR_NAME} PUBLIC -DVIKR_CURRENT_VERSION=0x000601)

target_link_libraries(${VIKR_NAME} assimp)
target_link_libraries(${VIKR_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${VIKR_NAME} freetype)

# Simple Tests.
add_subdirectory(test/opengl_testing)
add_subdirectory(test/vulkan_testing)
