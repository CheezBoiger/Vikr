//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_COMMAND_HPP
#define __VIKR_RENDER_COMMAND_HPP


#include <platform/vikr_types.hpp>
#include <vector>


namespace vikr {


/**
  Various other commands going in, but this is enough for now...
*/
enum RenderCommandType {
  VIKR_MESH,
  VIKR_GROUP,
  VIKR_PRIMITIVE,
  VIKR_TRIANGLES
};


/**
  Abstract RenderCommand.
*/
class RenderCommand {
public:
  RenderCommand(RenderCommandType type);

protected:
  RenderCommandType type;
};


/**
  Custom RenderQueue for the Renderer.
*/
class RenderQueue {
public:
  vvoid PushBack(RenderCommand command);
  
protected:
  std::vector<RenderCommand> m_command_list; 
};
} // vikr
#endif // __VIKR_RENDER_COMMAND_HPP