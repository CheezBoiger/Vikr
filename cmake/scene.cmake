# scene
set(VIKR_SCENE_SRC_DIR ${VIKR_SRC_DIR}/scene/)
set(VIKR_SCENE_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/scene/)

set(VIKR_SCENE_COMPONENT_SRC_DIR ${VIKR_SCENE_SRC_DIR}/components/)
set(VIKR_SCENE_COMPONENT_INCLUDE_DIR ${VIKR_SCENE_INCLUDE_DIR}/components/)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_COMPONENT_SRC_DIR}/scene_component.cpp
  ${VIKR_SCENE_COMPONENT_SRC_DIR}/transform_component.cpp
  ${VIKR_SCENE_COMPONENT_SRC_DIR}/light_component.cpp
  ${VIKR_SCENE_COMPONENT_SRC_DIR}/camera_component.cpp
  ${VIKR_SCENE_COMPONENT_SRC_DIR}/mesh_component.cpp
  ${VIKR_SCENE_COMPONENT_SRC_DIR}/renderer_component.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_COMPONENT_INCLUDE_DIR}/scene_component.hpp
  ${VIKR_SCENE_COMPONENT_INCLUDE_DIR}/transform_component.hpp
  ${VIKR_SCENE_COMPONENT_INCLUDE_DIR}/light_component.hpp
  ${VIKR_SCENE_COMPONENT_INCLUDE_DIR}/camera_component.hpp
  ${VIKR_SCENE_COMPONENT_INCLUDE_DIR}/mesh_component.hpp
  ${VIKR_SCENE_COMPONENT_INCLUDE_DIR}/renderer_component.hpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_SRC_DIR}/first_person_camera.cpp
  ${VIKR_SCENE_SRC_DIR}/guid_generator.cpp
  ${VIKR_SCENE_SRC_DIR}/scene_node.cpp
  ${VIKR_SCENE_SRC_DIR}/scene.cpp
  ${VIKR_SCENE_SRC_DIR}/transform.cpp
  ${VIKR_SCENE_SRC_DIR}/camera.cpp
  ${VIKR_SCENE_SRC_DIR}/camera_frustum.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_INCLUDE_DIR}/icamera.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/first_person_camera.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/guid_generator.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/scene_node.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/scene.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/transform.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/camera.hpp
  ${VIKR_SCENE_INCLUDE_DIR}/camera_frustum.hpp
)