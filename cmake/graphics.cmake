# This is where we keep out configurations for graphics
# devices, context, and low level rendering.

set(VIKR_GRAPHICS_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/graphics/)
set(VIKR_GRAPHICS_SRC_DIR ${VIKR_SRC_DIR}/graphics/)


set(VIKR_GRAPHICS_VK_SRC_DIR       ${VIKR_SRC_DIR}/graphics/vk/)
set(VIKR_GRAPHICS_GL4_SRC_DIR      ${VIKR_SRC_DIR}/graphics/gl4/)

set(VIKR_GRAPHICS_VK_INCLUDE_DIR   ${VIKR_INCLUDE_DIR}/graphics/vk)
set(VIKR_GRAPHICS_GL4_INCLUDE_DIR  ${VIKR_INCLUDE_DIR}/graphics/gl4)


if (vulkan)

  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_vertexbuffer.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_surface.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_instance.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_logdevice.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_phydevice.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_graphics_pipeline_state.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_compute_pipeline_state.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_device.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_renderpass.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_framebuffer.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_uniformbuffer.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_storagebuffer.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_swapchain.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_commandbuffer.cpp
    ${VIKR_GRAPHICS_VK_SRC_DIR}/vk_rendertarget.cpp
  )

  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_renderpass.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_device.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_graphics_pipeline_state.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_compute_pipeline_state.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_phydevice.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_logdevice.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_instance.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_surface.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_vertexbuffer.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_framebuffer.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_uniformbuffer.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_storagebuffer.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_swapchain.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_commandbuffer.hpp
    ${VIKR_GRAPHICS_VK_INCLUDE_DIR}/vk_rendertarget.hpp
  )
endif()



# OpenGL Always enabled!
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_renderpass.cpp
#  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_vertexbuffer.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_commandbuffer.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_device.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_graphics_pipeline_state.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_compute_pipeline_state.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_framebuffer.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_rendertarget.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_uniformbuffer.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_storagebuffer.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_rendertarget.cpp
  ${VIKR_GRAPHICS_GL4_SRC_DIR}/gl4_context.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/opengl.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_rendertarget.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_graphics_command.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_framebuffer.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_graphics_pipeline_state.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_compute_pipeline_state.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_device.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_commandbuffer.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_vertexbuffer.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_renderpass.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_context.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_uniformbuffer.hpp
  ${VIKR_GRAPHICS_GL4_INCLUDE_DIR}/gl4_storagebuffer.hpp
)



set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_GRAPHICS_INCLUDE_DIR}/graphics_config.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/graphics.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/blendmode.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/cullmode.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/depthmode.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/stencildepth.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/viewport.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/vertexbuffer.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/graphics_pipeline_state.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/compute_pipeline_state.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/command_buffer.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/framebuffer.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/render_target.hpp
  ${VIKR_GRAPHICS_SRC_DIR}/render_target.cpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/render_pass.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/render_device.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/topology.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/uniformbuffer.hpp
  ${VIKR_GRAPHICS_INCLUDE_DIR}/storagebuffer.hpp
)

