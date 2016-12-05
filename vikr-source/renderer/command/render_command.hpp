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

/**
  Abstract RenderCommand. Perhaps useful cases, the best practice would be 
  to call an "Execute()" function with an OpenGL or Vulkan context. 
  This might be considered for future designs. 
*/
class RenderCommand {
  static const std::string kDefaultName;
public:
  RenderCommand(RenderCommandType type);
  RenderCommand(RenderCommand&& rendercommand) = default;
  RenderCommand& operator=(RenderCommand&& render_command) = default;
  RenderCommandType GetCommandType() { return type; }

  std::string GetCommandName() { return m_name; }
  vvoid SetCommandName(std::string name) { m_name = name; }

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