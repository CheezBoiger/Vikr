//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MATERIAL_HPP
#define __VIKR_MATERIAL_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/cullmode.hpp>
#include <renderer/blendmode.hpp>
#include <renderer/depthmode.hpp>
#include <unordered_map>
#include <string>

namespace vikr {


class Shader;


/**
  Material defines the textures, cull, and blend of the Mesh.
*/
class Material {
  static const std::string kDefaultName;
public:
  Material(Shader *shader, std::string name);
  Material(Shader *shader);
  Shader *GetShader() { return m_shader; }

  vvoid SetFrontFace(FrontFace mode) { m_frontface = mode; }
  vvoid SetCullFace(CullFace face) { m_cullface = face; }
  vvoid SetIsBlending(vbool blend) { is_blending = blend; }
  vvoid SetBlendDst(BlendFunc funct) { m_blend_dst = funct; }
  vvoid SetBlendSrc(BlendFunc funct) { m_blend_src = funct; }  

  vbool IsBlending() { return is_blending; }
  vbool IsCulling() { return is_culling; }
  vbool HasDepth() { return has_depth; }

  CullFace GetCullFace() { return m_cullface; }
  FrontFace GetFrontFace() { return m_frontface; }
  DepthFunc GetDepthFunc() { return m_depth_func; }

  BlendFunc GetBlendSrc() { return m_blend_src; }
  BlendFunc GetBlendDst() { return m_blend_dst; }
  

protected:
  std::string m_name;
  Shader *m_shader; // weak ref

  vbool has_depth;
  DepthFunc m_depth_func;

  vbool is_culling;
  FrontFace m_frontface;
  CullFace m_cullface;

  vbool is_blending;
  BlendFunc m_blend_src;
  BlendFunc m_blend_dst;
  BlendEq m_blend_equation;
}; 
} // vikr
#endif // __VIKR_MATERIAL_HPP