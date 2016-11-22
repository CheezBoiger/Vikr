# GLAD.cmake holds the files and settings for the Glad directory inside vikr.

set(VIKR_GLAD_PRIVATE_DIR ${VIKR_GLAD_DIR}/private/)
set(VIKR_GLAD_PUBLIC_DIR ${VIKR_GLAD_DIR}/public/)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GLAD_DIR}/glad.c
  ${VIKR_GLAD_DIR}/glad.h
  ${VIKR_GLAD_DIR}/khrplatform.h)