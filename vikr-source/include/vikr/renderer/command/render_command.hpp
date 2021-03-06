//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_COMMAND_HPP
#define __VIKR_RENDER_COMMAND_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/renderer/command/render_command_types.hpp>

#include <string>

namespace vikr {


class Renderer;
class Commandbuffer;
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
  virtual vvoid Record(Commandbuffer &buffer) = 0;

  vvoid SetDrawOrder(vint32 order) { m_drawOrder = order; }
  vint32 GetDrawOrder() { return m_drawOrder; }

protected:
  RenderCommandType type;

private:
  /**
    Name of the command.
  */
  std::string m_name;

  /**
    order of draw.
  */
  vint32 m_drawOrder          = 0;

  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderCommand);
};
} // vikr
#endif // __VIKR_RENDER_COMMAND_HPP