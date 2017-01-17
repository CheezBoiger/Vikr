//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/command/render_command.hpp>


namespace vikr {


const std::string RenderCommand::kDefaultName = "Default_renderCommand";


RenderCommand::RenderCommand(RenderCommandType type)
  : type(type)
  , m_name(kDefaultName)
{
}
} // vikr