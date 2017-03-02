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
    MaterialValue mat;
    mat.m_mat4 = m_transform->GetTransform();
    mat.type = vikr_UNIFORM_MAT4;
    m_transformParam["vikr_Model"] = mat;
    ShaderUniformParams param;
    param.uniforms = &m_transformParam;
    buffer.SetShaderUniforms(param);
  }


  Transform *m_transform;

private:

  std::map<std::string, MaterialValue> m_transformParam;
  VIKR_DISALLOW_COPY_AND_ASSIGN(TransformCommand);
};
} // vikr
#endif // __VIKR_TRANSFORM_COMMAND_HPP