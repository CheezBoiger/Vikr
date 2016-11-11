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
set(VIKR_VERSION "0.01")


# concat the name!
set(VIKR_NAME "Vikr")

# Vikr Rendering engine directories
set(VIKR_SOURCE_DIR   vikr-source/)
set(VIKR_GLAD_DIR     ${VIKR_SOURCE_DIR}/glad/)
set(VIKR_PLATFORM_DIR ${VIKR_SOURCE_DIR}/platform/)
set(VIKR_RENDERER_DIR ${VIKR_SOURCE_DIR}/renderer/)
set(VIKR_GRAPHICS_DIR ${VIKR_PLATFORM_DIR}/graphics/)
set(VIKR_SHADER_DIR   ${VIKR_SOURCE_DIR}/shader/)
set(VIKR_SCENE_DIR    ${VIKR_SOURCE_DIR}/scene/)
set(VIKR_UTIL_DIR     ${VIKR_SOURCE_DIR}/util/)

# Set the directories for the compiler
include_directories(SYSTEM ${VIKR_SOURCE_DIR})
# Set Library directories as well
include_directories(SYSTEM libs/include/)

# Setting up the glob.
set(VIKR_GLOB)

# These will have to move soon.
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SOURCE_DIR}/vikr.hpp
  ${VIKR_SOURCE_DIR}/vikr.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GLAD_DIR}/glad.c
  ${VIKR_GLAD_DIR}/glad.h
  ${VIKR_GLAD_DIR}/khrplatform.h)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_UTIL_DIR}/vikr_assert.hpp
  ${VIKR_UTIL_DIR}/vikr_filesystem.hpp
  ${VIKR_UTIL_DIR}/vikr_log.hpp
  ${VIKR_UTIL_DIR}/vikr_log.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_PLATFORM_DIR}/platform.hpp
  ${VIKR_PLATFORM_DIR}/vikr_time.hpp
  ${VIKR_PLATFORM_DIR}/vikr_types.hpp
  ${VIKR_PLATFORM_DIR}/vikr_api.hpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_DIR}/icamera.hpp
  ${VIKR_SCENE_DIR}/camera.hpp
  ${VIKR_SCENE_DIR}/camera.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GRAPHICS_DIR}/opengl.hpp
  ${VIKR_GRAPHICS_DIR}/vk.hpp
  ${VIKR_GRAPHICS_DIR}/graphics.hpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_DIR}/irenderer.hpp
  ${VIKR_RENDERER_DIR}/renderer.hpp
  ${VIKR_RENDERER_DIR}/vkrenderer.hpp
  ${VIKR_RENDERER_DIR}/glrenderer.hpp
  ${VIKR_RENDERER_DIR}/render_command.hpp
  ${VIKR_RENDERER_DIR}/render_group.hpp
  ${VIKR_RENDERER_DIR}/render_target.hpp
  ${VIKR_RENDERER_DIR}/viewport.hpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_DIR}/ishader.hpp
  ${VIKR_SHADER_DIR}/gl_shader.hpp
  ${VIKR_SHADER_DIR}/gl_shader.cpp
  ${VIKR_SHADER_DIR}/vk_shader.hpp
  ${VIKR_SHADER_DIR}/material.hpp)


if (${CMAKE_CXX_COMPILER_ID})
# Doing some stuff for organization.
endif()


set(VIKR_NAME "${VIKR_NAME}_${VIKR_VERSION}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/ ${CMAKE_CURRENT_SOURCE_DIR}/libs/Vulkan/)
# This will have to be changed up a bit though...
# A Rendering engine is usually broken up into pieces, is this ok though?
add_library(${VIKR_NAME} STATIC
  ${VIKR_GLOB})

# Version might need to be determined, as well as updating to compensate for static libs on OS's other than windows.
target_link_libraries(${VIKR_NAME} glfw3)
target_link_libraries(${VIKR_NAME} vulkan-1)


add_subdirectory(test/)

