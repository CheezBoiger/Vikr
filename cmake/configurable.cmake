# configurables for the files and their directories.

if (vulkan)
  message("Vulkan API enabled...")
  add_definitions(-DVIKR_VULKAN_ENABLED)
else()
endif()

if (debug)
 message("DEBUG MODE ON")
 add_definitions(-DVIKR_DEBUG_ENABLED)
endif()


# concat the name!
set(VIKR_NAME "Vikr")

# Vikr Rendering engine directories
set(VIKR_SOURCE_DIR             vikr-source/)
set(VIKR_GLAD_DIR               ${VIKR_SOURCE_DIR}/glad/)
set(VIKR_PLATFORM_DIR           ${VIKR_SOURCE_DIR}/platform/)
set(VIKR_RENDERER_DIR           ${VIKR_SOURCE_DIR}/renderer/)
set(VIKR_PLATFORM_GRAPHICS_DIR  ${VIKR_PLATFORM_DIR}/graphics/)
set(VIKR_GRAPHICS_DIR           ${VIKR_SOURCE_DIR}/graphics/)
set(VIKR_SHADER_DIR             ${VIKR_SOURCE_DIR}/shader/)
set(VIKR_STB_DIR                ${VIKR_SHADER_DIR}/stb/)
set(VIKR_SCENE_DIR              ${VIKR_SOURCE_DIR}/scene/)
set(VIKR_UTIL_DIR               ${VIKR_SOURCE_DIR}/util/)
set(VIKR_INPUT_DIR              ${VIKR_SOURCE_DIR}/input/)
set(VIKR_MESH_DIR               ${VIKR_SOURCE_DIR}/mesh/)
set(VIKR_MATH_DIR               ${VIKR_SOURCE_DIR}/math/)
set(VIKR_ALG_DIR                ${VIKR_MATH_DIR}/alg/)
set(VIKR_SHAPE_DIR              ${VIKR_MATH_DIR}/shape/)
set(VIKR_LIGHTING_DIR           ${VIKR_SOURCE_DIR}/lighting/)
set(VIKR_RESOURCES_DIR          ${VIKR_SOURCE_DIR}/resources/)
set(VIKR_TOOLS_DIR              ${VIKR_SOURCE_DIR}/tools/)

# Set the directories for the compiler
include_directories(SYSTEM ${VIKR_SOURCE_DIR})
# Set Library directories as well
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