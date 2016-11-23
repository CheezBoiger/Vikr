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
set(VIKR_VERSION "v0.01")
option(vulkan "Build Vikr with Vulkan extension." OFF)
option(debug "debug the software." OFF)


include(cmake/configurable.cmake)


if (${CMAKE_CXX_COMPILER_ID})
# Doing some stuff for organization.
  foreach(source IN LISTS VIKR_GLOB)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
  endforeach()
endif()


set(VIKR_NAME "${VIKR_NAME}_${VIKR_VERSION}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/ ${CMAKE_CURRENT_SOURCE_DIR}/libs/Vulkan/bin32/ 
                 ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/)

# This will have to be changed up a bit though...
# A Rendering engine is usually broken up into pieces, is this ok though?
add_library(${VIKR_NAME} STATIC
  ${VIKR_GLOB})

# Version might need to be determined, as well as updating to compensate for static libs on OS's other than windows.
target_link_libraries(${VIKR_NAME} glfw3)
target_link_libraries(${VIKR_NAME} vulkan-1)
target_link_libraries(${VIKR_NAME} assimp)
target_link_libraries(${VIKR_NAME} opengl32)

add_subdirectory(test/)
