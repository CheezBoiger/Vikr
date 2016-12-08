# Mesh

set(VIKR_OPENGL_MESH_DIR ${VIKR_MESH_DIR}/opengl/)
set(VIKR_VULKAN_MESH_DIR ${VIKR_MESH_DIR}/vulkan/)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_MESH_DIR}/vertex.hpp
  ${VIKR_MESH_DIR}/model.hpp
  ${VIKR_MESH_DIR}/model.cpp
  ${VIKR_MESH_DIR}/imesh.hpp
  ${VIKR_MESH_DIR}/mesh.hpp
  ${VIKR_MESH_DIR}/mesh.cpp)