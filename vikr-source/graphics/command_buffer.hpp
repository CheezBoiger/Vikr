//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_COMMAND_BUFFER_HPP
#define __VIKR_COMMAND_BUFFER_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>

#include <vector>


namespace vikr {


class GraphicsCommand;

/**
  CommandBuffer to send to RenderContext. This is a raw commandbuffer,
  so sorting is not needed here.
*/
class CommandBuffer {
public:
  CommandBuffer();

  vvoid Clear();

  vvoid Pushback(GraphicsCommand *command);
  
  std::vector<GraphicsCommand *> &GetCommands() { return commands; }


  

private:

  std::vector<GraphicsCommand *> commands;
};
} // vikr
#endif // __VIKR_COMMAND_BUFFER_HPP