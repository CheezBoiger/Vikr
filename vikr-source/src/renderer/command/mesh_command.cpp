//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/command/mesh_command.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/graphics/command_buffer.hpp>


namespace vikr {


MeshCommand::MeshCommand()
  : RenderCommand(RenderCommandType::COMMAND_MESH)
{
}


vvoid MeshCommand::Record(Commandbuffer &buffer) {
  
}
} // vikr