//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_COMMAND_HPP
#define __VIKR_RENDER_COMMAND_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/render_command_types.hpp>


namespace vikr {


/**
  Abstract RenderCommand.
*/
class RenderCommand {
public:
  RenderCommand(RenderCommandType type);
  
protected:
  RenderCommandType type;

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderCommand);
};
} // vikr
#endif // __VIKR_RENDER_COMMAND_HPP