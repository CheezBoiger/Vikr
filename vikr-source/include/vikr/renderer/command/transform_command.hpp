//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_COMMAND_HPP
#define __VIKR_TRANSFORM_COMMAND_HPP


#include <vikr/renderer/command/render_command.hpp>
#include <vikr/renderer/command/render_command_types.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/scene/transform.hpp>
#include <vikr/shader/material.hpp>

#include <map>
#include <memory>


namespace vikr {


class Transform;


class TransformCommand : public RenderCommand {
public:

  TransformCommand(Transform *transform = nullptr) 
    : RenderCommand(RenderCommandType::COMMAND_TRANSFORM)
    , m_transform(transform) { 
    }


  vvoid Record(Commandbuffer &buffer) override {
    buffer.BeginRecord();
    m_material.SetMat4("vikr_Model", m_transform->GetTransform());
    buffer.SetMaterial(&m_material);
    buffer.EndRecord();
  }


  Transform *m_transform;

private:
  Material m_material;
  VIKR_DISALLOW_COPY_AND_ASSIGN(TransformCommand);
};
} // vikr
#endif // __VIKR_TRANSFORM_COMMAND_HPP