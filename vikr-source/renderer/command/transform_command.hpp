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
  VIKR_DEFAULT_MOVE_AND_ASSIGN(TransformCommand);

  TransformCommand(Transform *transform = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_TRANSFORM)
    , m_transform(transform) { }

  vvoid Record(CommandBuffer *buffer) override {
    
  }

  Transform *m_transform;
private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(TransformCommand);
};
} // vikr
#endif // __VIKR_TRANSFORM_COMMAND_HPP