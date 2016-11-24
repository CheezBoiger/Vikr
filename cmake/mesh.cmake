# Mesh

set(VIKR_OPENGL_MESH_DIR ${VIKR_MESH_DIR}/opengl/)
set(VIKR_VULKAN_MESH_DIR ${VIKR_MESH_DIR}/vulkan/)


if (vulkan)
  set(VIKR_GLOB 
    ${VIKR_GLOB}
    ${VIKR_VULKAN_MESH_DIR}/vkmesh.hpp
    ${VIKR_VULKAN_MESH_DIR}/vkmesh.cpp)
endif()


# OpenGL always supported!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_OPENGL_MESH_DIR}/glmesh.hpp
  ${VIKR_OPENGL_MESH_DIR}/glmesh.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_MESH_DIR}/model.hpp
  ${VIKR_MESH_DIR}/model.cpp
  ${VIKR_MESH_DIR}/imesh.hpp
  ${VIKR_MESH_DIR}/mesh.hpp
  ${VIKR_MESH_DIR}/mesh.cpp)