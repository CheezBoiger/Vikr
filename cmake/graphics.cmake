# This is where we keep out configurations for graphics
# devices, context, and low level rendering.


set(VIKR_GRAPHICS_VK_DIR ${VIKR_GRAPHICS_DIR}/vk/)
set(VIKR_GRAPHICS_GL4_DIR ${VIKR_GRAPHICS_DIR}/gl4/)


if (vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_GRAPHICS_VK_DIR}/vk_context.cpp
    ${VIKR_GRAPHICS_VK_DIR}/vk_context.hpp
    ${VIKR_GRAPHICS_VK_DIR}/vk_pipeline_state.hpp
    ${VIKR_GRAPHICS_VK_DIR}/vk_pipeline_state.cpp
    ${VIKR_GRAPHICS_VK_DIR}/vk_device.hpp
    ${VIKR_GRAPHICS_VK_DIR}/vk_device.cpp)
endif()



# OpenGL Always enabled!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_context.hpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_context.cpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_device.hpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_device.cpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_pipeline_state.hpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_pipeline_state.cpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_framebuffer.hpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_framebuffer.cpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_rendertarget.hpp
  ${VIKR_GRAPHICS_GL4_DIR}/gl4_rendertarget.cpp)



set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GRAPHICS_DIR}/blendmode.hpp
  ${VIKR_GRAPHICS_DIR}/cullmode.hpp
  ${VIKR_GRAPHICS_DIR}/depthmode.hpp
  ${VIKR_GRAPHICS_DIR}/stencildepth.hpp
  ${VIKR_GRAPHICS_DIR}/viewport.hpp
  ${VIKR_GRAPHICS_DIR}/graphics_command.hpp
  ${VIKR_GRAPHICS_DIR}/graphics_command.cpp
  ${VIKR_GRAPHICS_DIR}/pipeline_state.hpp
  ${VIKR_GRAPHICS_DIR}/command_buffer.hpp
  ${VIKR_GRAPHICS_DIR}/command_buffer.cpp
  ${VIKR_GRAPHICS_DIR}/framebuffer.hpp
  ${VIKR_GRAPHICS_DIR}/render_target.hpp
  ${VIKR_GRAPHICS_DIR}/render_target.cpp
  ${VIKR_GRAPHICS_DIR}/render_pass.hpp
  ${VIKR_GRAPHICS_DIR}/render_context.hpp
  ${VIKR_GRAPHICS_DIR}/render_device.hpp
  ${VIKR_GRAPHICS_DIR}/topology.hpp)