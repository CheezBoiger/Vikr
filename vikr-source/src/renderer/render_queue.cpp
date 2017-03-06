//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/renderer/render_queue.hpp>
#include <vikr/renderer/command/render_command.hpp>
#include <vikr/graphics/render_target.hpp>


#include <algorithm>


namespace vikr {


vvoid RenderQueue::PushBack(RenderCommand *command) {
  if (command) {
    m_commands.push_back(command);
  }
}


vvoid RenderQueue::Sort() {
  std::sort(deferred_commands.begin(), deferred_commands.end(), deferred_comparator);
  // Standard sort using custom sorting callback.
  std::sort(m_commands.begin(), m_commands.end(), sorting_comparator);
}


vvoid RenderQueue::Clear() {
  deferred_commands.clear();
  m_commands.clear();
}



} // vikr