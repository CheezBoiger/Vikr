# resources

set(VIKR_RESOURCES_OPENGL_DIR ${VIKR_RESOURCES_DIR}/opengl/)
set(VIKR_RESOURCES_VULKAN_DIR ${VIKR_RESOURCES_DIR}/vulkan/)

if (vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RESOURCES_VULKAN_DIR}/vk_resource_manager.hpp)
endif()

# OpenGL always supported!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_OPENGL_DIR}/gl_resource_manager.hpp
  ${VIKR_RESOURCES_OPENGL_DIR}/gl_resource_manager.cpp)


set (VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_DIR}/renderer_builder.hpp
  ${VIKR_RESOURCES_DIR}/resource_manager.cpp
  ${VIKR_RESOURCES_DIR}/resource_manager.hpp)