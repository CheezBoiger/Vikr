# GLAD.cmake holds the files and settings for the Glad directory inside vikr.

set(VIKR_GLAD_SRC_DIR ${VIKR_SRC_DIR}/glad)
set(VIKR_GLAD_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/glad)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GLAD_SRC_DIR}/glad.c
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GLAD_INCLUDE_DIR}/glad.h
  ${VIKR_GLAD_INCLUDE_DIR}/khrplatform.h
)