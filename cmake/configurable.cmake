# configurables for the files and their directories.

set(ASSIMP_INCLUDE_DIR libs/assimp/include)
set(GLSLANG_INCLUDE_DIR libs/glslang)
set(GLFW_INCLUDE_DIR libs/glfw/include/GLFW)

find_package(Vulkan)
if (vulkan AND VULKAN_FOUND)
  message("Vulkan API enabled...")
  set(VULKAN_INCLUDE_DIR ${Vulkan_INCLUDE_DIRS})
  add_definitions(-DVIKR_VULKAN_ENABLED)
  include_directories(SYSTEM ${GLSLANG_INCLUDE_DIR})
  include_directories(SYSTEM ${VULKAN_INCLUDE_DIR})
elseif(vulkan AND NOT VULKAN_FOUND)
 message(FATAL_ERROR "Vulkan not found, cannot continue with \"vulkan\" command")
endif()

if (debug)
 message("DEBUG MODE ON")
 add_definitions(-DVIKR_DEBUG_ENABLED)
endif()


# concat the name!
set(VIKR_NAME "Vikr")

# Vikr Rendering engine directories
set(VIKR_SRC_DIR                     vikr-source/src/)
set(VIKR_INCLUDE_DIR                 vikr-source/include/vikr/)
set(VIKR_PUBLIC_DIR                  vikr-source/include/)


# Set the directories for the compiler
include_directories(SYSTEM ${VIKR_PUBLIC_DIR})
# Set Library directories as well
include_directories(SYSTEM ${GLFW_INCLUDE_DIR})
include_directories(SYSTEM ${ASSIMP_INCLUDE_DIR})
include_directories(SYSTEM libs/include/)

# Setting up the glob.
set(VIKR_GLOB)

include(cmake/glad.cmake)
include(cmake/input.cmake)
include(cmake/lighting.cmake)
include(cmake/graphics.cmake)
include(cmake/math.cmake)
include(cmake/mesh.cmake)
include(cmake/platform.cmake)
include(cmake/renderer.cmake)
include(cmake/scene.cmake)
include(cmake/shader.cmake)
include(cmake/util.cmake)
include(cmake/resources.cmake)
include(cmake/tools.cmake)
include(cmake/vikr.cmake)