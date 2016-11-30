//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/render_queue.hpp>
#include <renderer/render_command.hpp>
#include <renderer/render_target.hpp>


namespace vikr {


vvoid RenderQueue::PushBack(RenderCommand *command, RenderPass *target) {
  if (command && target) {
    m_command_map[target].push_back(command);
  }
}


vvoid RenderQueue::Sort() {
  std::sort(postbatch_commands.begin(), postbatch_commands.end(), deferred_comparator);
  // Standard sort using custom sorting callback.
  for (std::pair<RenderPass *, std::vector<RenderCommand *>> command : m_command_map) {
    std::sort(command.second.begin(), command.second.end(), sorting_comparator);
  }
}


vvoid RenderQueue::Clear() {
  postbatch_commands.clear();
  m_command_map.clear();
}



} // vikr