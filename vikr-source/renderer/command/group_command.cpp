//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/command/group_command.hpp>
#include <algorithm>


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


vvoid GroupCommand::Sort() {
  std::sort(m_commands.begin(), m_commands.end(), 
    [] (std::pair<guid_t, RenderCommand *> &command1,
        std::pair<guid_t, RenderCommand *> &command2) -> vint32
    {
      if (command1.second->GetCommandType() > command2.second->GetCommandType()) {
        return true;
      } else {
        return false;
      }
    });
}
} // vikr