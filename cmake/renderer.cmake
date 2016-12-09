# renderer

set(VIKR_RENDERER_OPENGL_DIR ${VIKR_RENDERER_DIR}/opengl/)
set(VIKR_RENDERER_VULKAN_DIR ${VIKR_RENDERER_DIR}/vulkan/)
set(VIKR_RENDERER_COMMAND_DIR ${VIKR_RENDERER_DIR}/command/)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_COMMAND_DIR}/render_command_types.hpp
  ${VIKR_RENDERER_COMMAND_DIR}/camera_command.hpp
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
  ${VIKR_RENDERER_DIR}/render_queue.hpp
  ${VIKR_RENDERER_DIR}/render_queue.cpp)