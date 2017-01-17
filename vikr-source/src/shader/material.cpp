//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/shader/material.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/util/vikr_log.hpp>

namespace vikr {

const std::string Material::kDefaultName = "default";


Material::Material(Shader *shader, std::string name)
  : m_name(name)
  , m_shader(shader)
{
}

Material::Material(Shader *shader)
  : m_name(kDefaultName)
  , m_shader(shader)
{
}


Material::Material()
  : Material(nullptr)
{
}


vvoid Material::SetTexture(std::string name, Texture *texture, vuint32 i) {
  if (texture) {
    m_uniform_samplers[name].texture = texture;
    m_uniform_samplers[name].i = i;
    switch (texture->GetTargetFormat()) {
      case vikr_TEXTURE_2D:       m_uniform_samplers[name].type = vikr_SAMPLER2D;    break;
      case vikr_TEXTURE_3D:       m_uniform_samplers[name].type = vikr_SAMPLER3D;    break;
      case vikr_TEXTURE_CUBEMAP:  m_uniform_samplers[name].type = vikr_SAMPLERCUBE;  break;
      default:                    m_uniform_samplers[name].type = vikr_SAMPLER2D;    break;
    }
  }

  m_material_values[name].m_integer = i;
  m_material_values[name].type = vikr_INT;
}


vvoid Material::SetBool(std::string name, vbool value) {
  m_material_values[name].m_bool = value;
  m_material_values[name].type = vikr_BOOL;
}


vvoid Material::SetInt(std::string name, vint32 value) {
  m_material_values[name].m_integer = value;
  m_material_values[name].type = vikr_INT;
}


vvoid Material::SetFloat(std::string name, vreal32 value) {
  m_material_values[name].m_float = value;
  m_material_values[name].type = vikr_FLOAT;  
}


vvoid Material::SetDouble(std::string name, vreal64 value) {
  m_material_values[name].m_double = value;
  m_material_values[name].type = vikr_DOUBLE;
}


vvoid Material::SetMat2(std::string name, glm::mat2 value) {
  m_material_values[name].m_mat2 = value;
  m_material_values[name].type = vikr_MAT2;
}


vvoid Material::SetMat3(std::string name, glm::mat3 value) {
  m_material_values[name].m_mat3 = value;
  m_material_values[name].type = vikr_MAT3;
}


vvoid Material::SetMat4(std::string name, glm::mat4 value) {
  m_material_values[name].m_mat4 = value;
  m_material_values[name].type = vikr_MAT4;
}


vvoid Material::SetVector2fv(std::string name, glm::vec2 value) {
  m_material_values[name].m_vec2 = value;
  m_material_values[name].type = vikr_VEC2;
}


vvoid Material::SetVector3fv(std::string name, glm::vec3 value) {
  m_material_values[name].m_vec3 = value;
  m_material_values[name].type = vikr_VEC3;
}


vvoid Material::SetVector4fv(std::string name, glm::vec4 value) {
  m_material_values[name].m_vec4 = value;
  m_material_values[name].type = vikr_VEC4;
}
} // vikr