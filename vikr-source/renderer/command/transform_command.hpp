//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_COMMAND_HPP
#define __VIKR_TRANSFORM_COMMAND_HPP

#include <renderer/command/render_command.hpp>
#include <renderer/command/render_command_types.hpp>

namespace vikr {


class Transform;


class TransformCommand : public RenderCommand {
public:
  TransformCommand(Transform *transform = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_TRANSFORM)
    , m_transform(transform) { }


  Transform *m_transform;
};
} // vikr
#endif // __VIKR_TRANSFORM_COMMAND_HPP