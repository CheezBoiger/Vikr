# utility
set(VIKR_UTIL_SRC_DIR ${VIKR_SRC_DIR}/util/)
set(VIKR_UTIL_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/util/)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_UTIL_SRC_DIR}/vikr_log.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_UTIL_INCLUDE_DIR}/vikr_assert.hpp
  ${VIKR_UTIL_INCLUDE_DIR}/vikr_filesystem.hpp
  ${VIKR_UTIL_INCLUDE_DIR}/vikr_log.hpp
)