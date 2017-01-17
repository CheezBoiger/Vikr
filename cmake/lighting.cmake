# lighting

set(VIKR_LIGHTING_SRC_DIR ${VIKR_SRC_DIR}/lighting/)
set(VIKR_LIGHTING_INCLUDE_DIR  ${VIKR_INCLUDE_DIR}/lighting/)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_LIGHTING_SRC_DIR}/point_light.cpp
  ${VIKR_LIGHTING_SRC_DIR}/directional_light.cpp
  ${VIKR_LIGHTING_SRC_DIR}/spot_light.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_LIGHTING_INCLUDE_DIR}/spot_light.hpp
  ${VIKR_LIGHTING_INCLUDE_DIR}/light.hpp
  ${VIKR_LIGHTING_INCLUDE_DIR}/point_light.hpp
  ${VIKR_LIGHTING_INCLUDE_DIR}/directional_light.hpp
)