//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/command/group_command.hpp>


namespace vikr {


RenderCommand *GroupCommand::Remove(guid_t guid) {
  RenderCommand *removed = nullptr;
  for (auto it = m_commands.begin();
       it != m_commands.end();
       ++it)
  {
    if (it->first == guid) {
      m_commands.erase(it);
      break;
    }
  }
  return removed;
}
} // vikr