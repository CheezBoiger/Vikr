//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/group_command.hpp>


namespace vikr {


RenderCommand *GroupCommand::Remove(std::string name) {
  RenderCommand *removed = nullptr;
  for (RenderCommand *command : m_commands) {
    // Needs to be implemented!
  }
  return removed;
}
} // vikr