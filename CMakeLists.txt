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
set(VIKR_VERSION "v0.5")
option(vulkan "Build Vikr with Vulkan extension." OFF)
option(debug "debug the software." OFF)


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

target_link_libraries(${VIKR_NAME} assimp)
target_link_libraries(${VIKR_NAME} opengl32)
target_link_libraries(${VIKR_NAME} freetype)

add_subdirectory(test/)
