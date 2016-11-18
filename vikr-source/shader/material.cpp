#include <shader/material.hpp>
#include <shader/texture.hpp>


namespace vikr {

const std::string Material::kDefaultName = "default";


Material::Material(Shader *shader, std::string name)
  : m_name(name)
  , m_shader(shader)
  , has_depth(true)
  , is_culling(false)
  , is_blending(false)
  , m_cullmode(CullMode::vikr_COUNTER_CLOCKWISE)
  , m_cullface(CullFace::vikr_BACK_FACE)
{
}

Material::Material(Shader *shader)
  : m_name(kDefaultName)
  , m_shader(shader)
  , has_depth(true)
  , is_culling(false)
  , is_blending(false)
  , m_cullmode(CullMode::vikr_COUNTER_CLOCKWISE)
  , m_cullface(CullFace::vikr_BACK_FACE)
{
}
} // vikr