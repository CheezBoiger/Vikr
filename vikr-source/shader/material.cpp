//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
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
  , m_depth_func(DepthFunc::vikr_DEPTH_LESS)
  , m_blend_src(BlendFunc::vikr_BLEND_SRC_ALPHA)
  , m_blend_dst(BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA)
  , m_blend_equation(BlendEq::vikr_BLEND_ADD)
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
  , m_depth_func(DepthFunc::vikr_DEPTH_LESS)
  , m_blend_src(BlendFunc::vikr_BLEND_SRC_ALPHA)
  , m_blend_dst(BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA)
  , m_blend_equation(BlendEq::vikr_BLEND_ADD)
{
}
} // vikr