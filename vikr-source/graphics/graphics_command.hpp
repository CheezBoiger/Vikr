//
// Copyright(c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_COMMAND_HPP
#define __VIKR_GRAPHICS_COMMAND_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>


namespace vikr {


class RenderContext;


/**
  Graphics command for the CommandBuffer to fill with.
*/
class GraphicsCommand {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GraphicsCommand);
  GraphicsCommand() { }
  virtual ~GraphicsCommand() { }

  /**
    Execute command.
  */
  virtual vvoid Execute(RenderContext *context) = 0;

private:

  VIKR_DISALLOW_COPY_AND_ASSIGN(GraphicsCommand);
};
} // vikr
#endif // __VIKR_GRAPHICS_COMMAND_HPP