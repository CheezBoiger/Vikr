//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GROUP_COMMAND_HPP
#define __VIKR_GROUP_COMMAND_HPP

#include <renderer/render_command.hpp>

#include <list>
#include <string>


namespace vikr {


/**
  Multiple groups of Commands to be executed.
*/
class GroupCommand : public RenderCommand {
public:
  GroupCommand() : RenderCommand(RenderCommandType::RENDER_GROUP) { }
  vvoid Insert(RenderCommand *command) { m_commands.push_back(command); }
  RenderCommand *Remove(std::string name);


  std::list<RenderCommand *>& GetCommands() { return m_commands; }  

private:
  std::list<RenderCommand *> m_commands;  
};
} // vikr
#endif // __VIKR_GROUP_COMMAND_HPP