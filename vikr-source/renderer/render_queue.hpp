//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_QUEUE_HPP
#define __VIKR_RENDER_QUEUE_HPP


#include <renderer/render_command.hpp>
#include <vector>


namespace vikr {


/**
Custom RenderQueue for the Renderer.
*/
class RenderQueue {
public:
  vvoid PushBack(RenderCommand command);
  vvoid Sort();
  vvoid Clear() { m_command_list.clear(); }

  std::vector<RenderCommand>& GetCommandList() { return m_command_list; }
protected:
  std::vector<RenderCommand> m_command_list;
};
} // vikr
#endif // __VIKR_RENDER_QUEUE_HPP