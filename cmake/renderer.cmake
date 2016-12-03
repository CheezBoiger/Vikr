# renderer

set(VIKR_RENDERER_OPENGL_DIR ${VIKR_RENDERER_DIR}/opengl/)
set(VIKR_RENDERER_VULKAN_DIR ${VIKR_RENDERER_DIR}/vulkan/)
set(VIKR_RENDERER_COMMAND_DIR ${VIKR_RENDERER_DIR}/command/)


if (vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_RENDERER_VULKAN_DIR}/vkrenderer.hpp
    ${VIKR_RENDERER_VULKAN_DIR}/vkrenderer.cpp)
endif()


# OpenGL is always Enabled
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_OPENGL_DIR}/gl_rendertarget.hpp
  ${VIKR_RENDERER_OPENGL_DIR}/gl_rendertarget.cpp
  ${VIKR_RENDERER_OPENGL_DIR}/glrenderer.hpp
  ${VIKR_RENDERER_OPENGL_DIR}/glrenderer.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_COMMAND_DIR}/render_command_types.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/manual_commands.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/manual_commands.cpp
  ${VIKR_RENDERER_COMMAND_DIR}/render_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/render_command.cpp
  ${VIKR_RENDERER_COMMAND_DIR}/primitive_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/light_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/material_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/transform_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/mesh_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/mesh_command.cpp
  ${VIKR_RENDERER_COMMAND_DIR}/debug_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/group_command.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/group_command.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_DIR}/irenderer.hpp
  ${VIKR_RENDERER_DIR}/renderer.hpp
  ${VIKR_RENDERER_DIR}/renderer.cpp
  ${VIKR_RENDERER_DIR}/render_group.hpp
  ${VIKR_RENDERER_DIR}/render_queue.hpp
  ${VIKR_RENDERER_DIR}/render_queue.cpp
  ${VIKR_RENDERER_DIR}/render_target.hpp
  ${VIKR_RENDERER_DIR}/render_target.cpp
  ${VIKR_RENDERER_DIR}/viewport.hpp
  ${VIKR_RENDERER_DIR}/blendmode.hpp
  ${VIKR_RENDERER_DIR}/depthmode.hpp
  ${VIKR_RENDERER_DIR}/stencildepth.hpp
  ${VIKR_RENDERER_DIR}/pass.hpp
  ${VIKR_RENDERER_DIR}/framebuffer.hpp
  ${VIKR_RENDERER_DIR}/cullmode.hpp)