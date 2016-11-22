//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_QUEUE_HPP
#define __VIKR_RENDER_QUEUE_HPP


#include <renderer/render_command.hpp>
#include <vector>
#include <memory>


namespace vikr {


/**
Custom RenderQueue for the Renderer.
*/
template<typename RenderObject = RenderCommand>
class RenderQueue {
public:
  vvoid PushBack(RenderObject *command) { m_command_list.push_back(command); }
  vvoid Sort() { } // for now.
  vvoid Clear() { m_command_list.clear(); }

  std::vector<RenderObject *>& GetCommandList() { return m_command_list; }
protected:
  std::vector<RenderObject *> m_command_list;
};
} // vikr
#endif // __VIKR_RENDER_QUEUE_HPP