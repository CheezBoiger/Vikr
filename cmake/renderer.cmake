# renderer

set(VIKR_RENDERER_SRC_DIR ${VIKR_SRC_DIR}/renderer/)
set(VIKR_RENDERER_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/renderer/)

set(VIKR_RENDERER_COMMAND_SRC_DIR ${VIKR_RENDERER_SRC_DIR}/command/)
set(VIKR_RENDERER_COMMAND_INCLUDE_DIR ${VIKR_RENDERER_INCLUDE_DIR}/command/)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_COMMAND_SRC_DIR}/manual_commands.cpp
  ${VIKR_RENDERER_COMMAND_SRC_DIR}/render_command.cpp
  ${VIKR_RENDERER_COMMAND_SRC_DIR}/mesh_command.cpp
  ${VIKR_RENDERER_COMMAND_SRC_DIR}/group_command.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/debug_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/group_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/primitive_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/light_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/material_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/transform_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/mesh_command.hpp      
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/render_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/render_command_types.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/camera_command.hpp
  ${VIKR_RENDERER_COMMAND_INCLUDE_DIR}/manual_commands.hpp
)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_SRC_DIR}/screen_quad.cpp
  ${VIKR_RENDERER_SRC_DIR}/gbuffer.cpp
  ${VIKR_RENDERER_SRC_DIR}/shadowmap.cpp
  ${VIKR_RENDERER_SRC_DIR}/renderer.cpp
  ${VIKR_RENDERER_SRC_DIR}/render_queue.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_RENDERER_INCLUDE_DIR}/screen_quad.hpp
  ${VIKR_RENDERER_INCLUDE_DIR}/gbuffer.hpp
  ${VIKR_RENDERER_INCLUDE_DIR}/render_queue.hpp
  ${VIKR_RENDERER_INCLUDE_DIR}/irenderer.hpp
  ${VIKR_RENDERER_INCLUDE_DIR}/renderer.hpp
  ${VIKR_RENDERER_INCLUDE_DIR}/shadowmap.hpp
)

