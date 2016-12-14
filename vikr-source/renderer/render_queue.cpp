//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/render_queue.hpp>
#include <renderer/command/render_command.hpp>
#include <graphics/render_target.hpp>


namespace vikr {


vvoid RenderQueue::PushBack(RenderCommand *command) {
  if (command) {
    m_commandBuffer.push_back(command);
  }
}


vvoid RenderQueue::Sort() {
  std::sort(deferred_commands.begin(), deferred_commands.end(), deferred_comparator);
  // Standard sort using custom sorting callback.
  std::sort(m_commandBuffer.begin(), m_commandBuffer.end(), sorting_comparator);
}


vvoid RenderQueue::Clear() {
  deferred_commands.clear();
  m_commandBuffer.clear();
}



} // vikr