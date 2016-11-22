# lighting

set(VIKR_LIGHTING_PRIVATE_DIR ${VIKR_LIGHTING_DIR}/private/)
set(VIKR_LIGHTING_PUBLIC_DIR  ${VIKR_LIGHTING_DIR}/public/)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_LIGHTING_DIR}/light.hpp
  ${VIKR_LIGHTING_DIR}/point_light.hpp
  ${VIKR_LIGHTING_DIR}/point_light.cpp
  ${VIKR_LIGHTING_DIR}/directional_light.hpp
  ${VIKR_LIGHTING_DIR}/directional_light.cpp
  ${VIKR_LIGHTING_DIR}/spot_light.hpp
  ${VIKR_LIGHTING_DIR}/spot_light.cpp)