# Platform 
set(VIKR_PLATFORM_SRC_DIR ${VIKR_SRC_DIR}/platform/)
set(VIKR_PLATFORM_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/platform/)

set(VIKR_PLATFORM_LINUX_DIR ${VIKR_PLATFORM_SRC_DIR}/linux/)
set(VIKR_PLATFORM_WIN32_DIR ${VIKR_PLATFORM_SRC_DIR}/win32/)

set(VIKR_PLATFORM_GRAPHICS_DIR ${VIKR_PLATFORM_INCLUDE_DIR}/graphics/)

# Configure Operating system Filesystem and configs.
if(WIN32)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_PLATFORM_WIN32_DIR}/win32_config.hpp
    ${VIKR_PLATFORM_WIN32_DIR}/win32_filesystem.hpp)
elseif(UNIX) # Linux is not necessarily unix, but ehh this will be an issue later on in life...
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_PLATFORM_LINUX_DIR}/linux_config.hpp
    ${VIKR_PLATFORM_LINUX_DIR}/linux_filesystem.hpp)
endif()

# Globbin' it up.
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_PLATFORM_INCLUDE_DIR}/platform.hpp
  ${VIKR_PLATFORM_INCLUDE_DIR}/vikr_time.hpp
  ${VIKR_PLATFORM_INCLUDE_DIR}/vikr_types.hpp
  ${VIKR_PLATFORM_INCLUDE_DIR}/vikr_api.hpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_PLATFORM_SRC_DIR}/vikr_time.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
)