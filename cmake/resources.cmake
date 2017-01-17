# resources

set(VIKR_RESOURCES_SRC_DIR ${VIKR_SRC_DIR}/resources/)
set(VIKR_RESOURCES_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/resources/)


set(VIKR_RESOURCES_OPENGL_SRC_DIR ${VIKR_RESOURCES_SRC_DIR}/opengl/)
set(VIKR_RESOURCES_OPENGL_INCLUDE_DIR ${VIKR_RESOURCES_INCLUDE_DIR}/opengl/)

set(VIKR_RESOURCES_VULKAN_SRC_DIR ${VIKR_RESOURCES_SRC_DIR}/vulkan/)
set(VIKR_RESOURCES_VULKAN_INCLUDE_DIR ${VIKR_RESOURCES_INCLUDE_DIR}/vulkan/)

set(VIKR_RESOURCES_VULKAN_DETAIL_DIR ${VIKR_RESOURCES_INCLUDE_DIR}/vulkan/detail/)

if (vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RESOURCES_VULKAN_INCLUDE_DIR}/vk_resource_manager.hpp
    ${VIKR_RESOURCES_VULKAN_INCLUDE_DIR}/vk_memorymanager.hpp
  )

  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RESOURCES_VULKAN_DETAIL_DIR}/vk_memorymanager.inl
  )

endif()

# OpenGL always supported!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_OPENGL_SRC_DIR}/gl_resource_manager.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_OPENGL_INCLUDE_DIR}/gl_resource_manager.hpp
)


set (VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_SRC_DIR}/model_loader.cpp
  ${VIKR_RESOURCES_SRC_DIR}/resource_manager.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RESOURCES_INCLUDE_DIR}/resource_manager.hpp
  ${VIKR_RESOURCES_INCLUDE_DIR}/renderer_builder.hpp
  ${VIKR_RESOURCES_INCLUDE_DIR}/model_loader.hpp
)

