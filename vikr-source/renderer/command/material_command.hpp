//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_MATERIAL_COMMAND_HPP
#define __VIKR_MATERIAL_COMMAND_HPP


#include <renderer/command/render_command.hpp>


namespace vikr {


class MaterialCommand : public RenderCommand {
public:
  MaterialCommand() 
    : RenderCommand(RenderCommandType::COMMAND_MATERIAL) { }

};
}  // vikr
#endif // __VIKR_MATERIAL_COMMAND_HPP