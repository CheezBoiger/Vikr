//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_PIPELINE_STATE_HPP
#define __VIKR_PIPELINE_STATE_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <graphics/blendmode.hpp>
#include <graphics/cullmode.hpp>
#include <graphics/depthmode.hpp>
#include <graphics/stencildepth.hpp>


namespace vikr {


class PipelineState {
public:
  PipelineState(Shader *shader);
  PipelineState(Shader *shader, std::string name);

  Shader *GetShader() { return m_shader; }
  vvoid SetShader(Shader * shader) { m_shader = shader; }


  /**
  Set the front face of the material (this kind of
  determines the culling for the renderer).
  */
  vvoid SetFrontFace(FrontFace mode) { m_frontface = mode; }
  vvoid SetCullFace(CullFace face) { m_cullface = face; }
  vvoid SetIsBlending(vbool blend) { is_blending = blend; }
  vvoid SetIsCulling(vbool culling) { is_culling = culling; }
  vvoid SetBlendDst(BlendFunc funct) { m_blend_dst = funct; }
  vvoid SetBlendSrc(BlendFunc funct) { m_blend_src = funct; }


  vvoid SetDepth(vbool depth) { has_depth = depth; }

  vbool IsBlending() { return is_blending; }
  vbool IsCulling() { return is_culling; }
  vbool HasDepth() { return has_depth; }

  CullFace GetCullFace() { return m_cullface; }
  FrontFace GetFrontFace() { return m_frontface; }
  DepthFunc GetDepthFunc() { return m_depth_func; }

  BlendFunc GetBlendSrc() { return m_blend_src; }
  BlendFunc GetBlendDst() { return m_blend_dst; }
  
  
private:

  /**
    Both the Vertex and Fragment shader. 
    Geometry shader is optional.
  */
  Shader    *m_shader;

  vbool     has_depth;
  DepthFunc m_depth_func;

  vbool     is_culling;
  FrontFace m_frontface;
  CullFace  m_cullface;

  vbool     is_blending;
  BlendFunc m_blend_src;
  BlendFunc m_blend_dst;
  BlendEq   m_blend_equation;

};
} // vikr
#endif // __VIKR_PIPELINE_STATE_HPP