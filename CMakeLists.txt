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


if (vulkan)
  message("Vulkan API enabled...")
  add_definitions(-DVIKR_VULKAN_ENABLED)
else()
endif()

# concat the name!
set(VIKR_NAME "Vikr")

# Vikr Rendering engine directories
set(VIKR_SOURCE_DIR   vikr-source/)
set(VIKR_GLAD_DIR     ${VIKR_SOURCE_DIR}/glad/)
set(VIKR_PLATFORM_DIR ${VIKR_SOURCE_DIR}/platform/)
set(VIKR_RENDERER_DIR ${VIKR_SOURCE_DIR}/renderer/)
set(VIKR_GRAPHICS_DIR ${VIKR_PLATFORM_DIR}/graphics/)
set(VIKR_SHADER_DIR   ${VIKR_SOURCE_DIR}/shader/)
set(VIKR_STB_DIR      ${VIKR_SHADER_DIR}/stb/)
set(VIKR_SCENE_DIR    ${VIKR_SOURCE_DIR}/scene/)
set(VIKR_UTIL_DIR     ${VIKR_SOURCE_DIR}/util/)
set(VIKR_INPUT_DIR    ${VIKR_SOURCE_DIR}/input/)
set(VIKR_MESH_DIR     ${VIKR_SOURCE_DIR}/mesh/)
set(VIKR_MATH_DIR     ${VIKR_SOURCE_DIR}/math/)
set(VIKR_ALG_DIR      ${VIKR_MATH_DIR}/alg/)
set(VIKR_SHAPE_DIR    ${VIKR_MATH_DIR}/shape/)
set(VIKR_LIGHTING_DIR ${VIKR_SOURCE_DIR}/lighting/)

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
  ${VIKR_SCENE_DIR}/first_person_camera.hpp
  ${VIKR_SCENE_DIR}/first_person_camera.cpp
  ${VIKR_SCENE_DIR}/scene_node.hpp
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
  ${VIKR_RENDERER_DIR}/renderer.cpp
  ${VIKR_RENDERER_DIR}/vkrenderer.hpp
  ${VIKR_RENDERER_DIR}/vkrenderer.cpp
  ${VIKR_RENDERER_DIR}/glrenderer.hpp
  ${VIKR_RENDERER_DIR}/glrenderer.cpp
  ${VIKR_RENDERER_DIR}/render_command.hpp
  ${VIKR_RENDERER_DIR}/mesh_command.hpp
  ${VIKR_RENDERER_DIR}/mesh_command.cpp
  ${VIKR_RENDERER_DIR}/render_command_types.hpp
  ${VIKR_RENDERER_DIR}/render_group.hpp
  ${VIKR_RENDERER_DIR}/render_queue.hpp
  ${VIKR_RENDERER_DIR}/render_target.hpp
  ${VIKR_RENDERER_DIR}/viewport.hpp
  ${VIKR_RENDERER_DIR}/program_state.hpp
  ${VIKR_RENDERER_DIR}/program_state.cpp
  ${VIKR_RENDERER_DIR}/framebuffer.hpp
  ${VIKR_RENDERER_DIR}/framebuffer.cpp
  ${VIKR_RENDERER_DIR}/cullmode.hpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_MESH_DIR}/model.hpp
  ${VIKR_MESH_DIR}/model.cpp
  ${VIKR_MESH_DIR}/imesh.hpp
  ${VIKR_MESH_DIR}/mesh.hpp
  ${VIKR_MESH_DIR}/mesh.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_DIR}/shader.hpp
  ${VIKR_SHADER_DIR}/shader.cpp
  ${VIKR_SHADER_DIR}/ishader.hpp
  ${VIKR_SHADER_DIR}/gl_shader.hpp
  ${VIKR_SHADER_DIR}/gl_shader.cpp
  ${VIKR_SHADER_DIR}/vk_shader.hpp
  ${VIKR_SHADER_DIR}/material.hpp
  ${VIKR_SHADER_DIR}/material.cpp
  ${VIKR_SHADER_DIR}/texture.hpp
  ${VIKR_SHADER_DIR}/texture.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_STB_DIR}/stb_image.h
  ${VIKR_STB_DIR}/stb_image.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_INPUT_DIR}/keyboard.hpp
  ${VIKR_INPUT_DIR}/keyboard.cpp
  ${VIKR_INPUT_DIR}/mouse.hpp
  ${VIKR_INPUT_DIR}/mouse.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_ALG_DIR}/mat.hpp
  ${VIKR_ALG_DIR}/mat_alg.hpp
  ${VIKR_ALG_DIR}/quaternion.hpp
  ${VIKR_ALG_DIR}/vect.hpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_MATH_DIR}/vikr_math.hpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHAPE_DIR}/cube.hpp
  ${VIKR_SHAPE_DIR}/cube.cpp
  ${VIKR_SHAPE_DIR}/quad.hpp
  ${VIKR_SHAPE_DIR}/quad.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_LIGHTING_DIR}/light.hpp
  ${VIKR_LIGHTING_DIR}/point_light.hpp
  ${VIKR_LIGHTING_DIR}/point_light.cpp
  ${VIKR_LIGHTING_DIR}/directional_light.hpp
  ${VIKR_LIGHTING_DIR}/directional_light.cpp
  ${VIKR_LIGHTING_DIR}/spot_light.hpp
  ${VIKR_LIGHTING_DIR}/spot_light.cpp)


if (${CMAKE_CXX_COMPILER_ID})
# Doing some stuff for organization.
  foreach(source IN LISTS VIKR_GLOB)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
  endforeach()
endif()


set(VIKR_NAME "${VIKR_NAME}_${VIKR_VERSION}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW/ ${CMAKE_CURRENT_SOURCE_DIR}/libs/Vulkan/bin32/)
# This will have to be changed up a bit though...
# A Rendering engine is usually broken up into pieces, is this ok though?
add_library(${VIKR_NAME} STATIC
  ${VIKR_GLOB})

# Version might need to be determined, as well as updating to compensate for static libs on OS's other than windows.
target_link_libraries(${VIKR_NAME} glfw3)
target_link_libraries(${VIKR_NAME} vulkan-1)


add_subdirectory(test/)

