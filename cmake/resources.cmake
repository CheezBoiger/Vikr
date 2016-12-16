# resources

set(VIKR_RESOURCES_OPENGL_DIR ${VIKR_RESOURCES_DIR}/opengl/)
set(VIKR_RESOURCES_VULKAN_DIR ${VIKR_RESOURCES_DIR}/vulkan/)
set(VIKR_RESOURCES_VULKAN_DETAIL_DIR ${VIKR_RESOURCES_DIR}/vulkan/detail/)

if (vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RESOURCES_VULKAN_DIR}/vk_resource_manager.hpp
    ${VIKR_RESOURCES_VULKAN_DIR}/vk_memorymanager.hpp)

  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RESOURCES_VULKAN_DETAIL_DIR}/vk_memorymanager.inl)

endif()

# OpenGL always supported!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_OPENGL_DIR}/gl_resource_manager.hpp
  ${VIKR_RESOURCES_OPENGL_DIR}/gl_resource_manager.cpp)


set (VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_DIR}/model_loader.hpp
  ${VIKR_RESOURCES_DIR}/model_loader.cpp
  ${VIKR_RESOURCES_DIR}/renderer_builder.hpp
  ${VIKR_RESOURCES_DIR}/resource_manager.cpp
  ${VIKR_RESOURCES_DIR}/resource_manager.hpp)