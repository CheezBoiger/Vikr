//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/command/mesh_command.hpp>
#include <shader/material.hpp>
#include <shader/shader.hpp>
#include <mesh/mesh.hpp>

namespace vikr {


MeshCommand::MeshCommand()
  : RenderCommand(RenderCommandType::COMMAND_MESH)
{
}


} // vikr