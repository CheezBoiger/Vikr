//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_PRIMITIVE_COMMAND_HPP
#define __VIKR_PRIMITIVE_COMMAND_HPP


#include <renderer/command/render_command.hpp>


namespace vikr {



class PrimitiveCommand : public RenderCommand {
public:
  PrimitiveCommand() 
    : RenderCommand(RenderCommandType::COMMAND_PRIMITIVE) { }

};
} // vikr
#endif // __VIKR_PRIMITIVE_COMMAND_HPP