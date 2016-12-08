//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_COMMAND_HPP
#define __VIKR_RENDER_COMMAND_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/command/render_command_types.hpp>


namespace vikr {


class Renderer;
class CommandBuffer;
class RenderContext;

/**
  Abstract RenderCommand. Perhaps useful cases, the best practice would be 
  to call an "Execute()" function with an OpenGL or Vulkan context. 
  This might be considered for future designs. this is an upper level
  Command buffer, which allows users to create their own commands to 
  run the Rendering APIs.
*/
class RenderCommand {
  static const std::string kDefaultName;
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(RenderCommand);

  RenderCommand(RenderCommandType type);
  RenderCommandType GetCommandType() { return type; }

  std::string GetCommandName() { return m_name; }
  vvoid SetCommandName(std::string name) { m_name = name; }

  /**
    Talk to command buffer, this is where you input commands 
    to the Rendering API.
  */
  virtual vvoid Record(CommandBuffer *buffer) = 0;

protected:
  RenderCommandType type;

private:
  /**
    Name of the command.
  */
  std::string m_name;

  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderCommand);
};
} // vikr
#endif // __VIKR_RENDER_COMMAND_HPP