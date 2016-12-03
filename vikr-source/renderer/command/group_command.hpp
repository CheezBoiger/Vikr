//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GROUP_COMMAND_HPP
#define __VIKR_GROUP_COMMAND_HPP

#include <renderer/command/render_command.hpp>
#include <scene/guid_generator.hpp>
#include <vector>
#include <string>


namespace vikr {


/**
  Multiple groups of Commands to be executed.
*/
class GroupCommand : public RenderCommand {
public:
  GroupCommand() : RenderCommand(RenderCommandType::COMMAND_GROUP) { }
  vvoid Insert(guid_t guid, RenderCommand *command) { 
    m_commands.push_back(std::make_pair(guid, command)); 
  }

  RenderCommand *Remove(guid_t guid);


  std::vector<std::pair<guid_t, RenderCommand *>>& GetCommands() { return m_commands; }  

private:
  std::vector<std::pair<guid_t, RenderCommand *> > m_commands;  
};
} // vikr
#endif // __VIKR_GROUP_COMMAND_HPP