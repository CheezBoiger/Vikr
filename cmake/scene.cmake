# scene
set(VIKR_SCENE_COMPONENT_DIR ${VIKR_SCENE_DIR}/components)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_COMPONENT_DIR}/scene_component.hpp
  ${VIKR_SCENE_COMPONENT_DIR}/scene_component.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SCENE_DIR}/icamera.hpp
  ${VIKR_SCENE_DIR}/first_person_camera.hpp
  ${VIKR_SCENE_DIR}/first_person_camera.cpp
  ${VIKR_SCENE_DIR}/guid_generator.hpp
  ${VIKR_SCENE_DIR}/guid_generator.cpp
  ${VIKR_SCENE_DIR}/scene_node.hpp
  ${VIKR_SCENE_DIR}/scene_node.cpp
  ${VIKR_SCENE_DIR}/scene.hpp
  ${VIKR_SCENE_DIR}/scene.cpp
  ${VIKR_SCENE_DIR}/transform.hpp
  ${VIKR_SCENE_DIR}/transform.cpp
  ${VIKR_SCENE_DIR}/camera.hpp
  ${VIKR_SCENE_DIR}/camera.cpp)