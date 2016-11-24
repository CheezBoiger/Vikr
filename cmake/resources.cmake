# resources

set(VIKR_RESOURCES_OPENGL_DIR ${VIKR_RESOURCES_DIR}/opengl/)
set(VIKR_RESOURCES_VULKAN_DIR ${VIKR_RESOURCES_DIR}/vulkan/)

if (vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RESOURCES_VULKAN_DIR}/vk_resources.hpp)
endif()

# OpenGL always supported!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_OPENGL_DIR}/gl_resources.hpp
  ${VIKR_RESOURCES_OPENGL_DIR}/gl_resources.cpp)


set (VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_DIR}/renderer_builder.hpp
  ${VIKR_RESOURCES_DIR}/resources.hpp)