# Input for most of the input inside vikr.

set(VIKR_INPUT_SRC_DIR ${VIKR_SRC_DIR}/input/)
set(VIKR_INPUT_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/input/)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_INPUT_SRC_DIR}/keyboard.cpp
  ${VIKR_INPUT_SRC_DIR}/mouse.cpp
  ${VIKR_INPUT_SRC_DIR}/window.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_INPUT_INCLUDE_DIR}/window.hpp
  ${VIKR_INPUT_INCLUDE_DIR}/mouse.hpp
  ${VIKR_INPUT_INCLUDE_DIR}/keyboard.hpp
)