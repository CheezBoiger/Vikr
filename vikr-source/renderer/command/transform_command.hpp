//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_COMMAND_HPP
#define __VIKR_TRANSFORM_COMMAND_HPP

#include <renderer/command/render_command.hpp>
#include <renderer/command/render_command_types.hpp>

namespace vikr {


class TransformCommand : public RenderCommand {
public:
  TransformCommand() 
    : RenderCommand(RenderCommandType::COMMAND_TRANSFORM) { }


};
} // vikr
#endif // __VIKR_TRANSFORM_COMMAND_HPP