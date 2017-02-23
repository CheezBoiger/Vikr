//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_PIPELINE_STATE_HPP
#define __VIKR_GL4_PIPELINE_STATE_HPP


#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/graphics/topology.hpp>

#include <vikr/shader/shader.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>

#include <map>
#include <string>


namespace vikr {



/**
  The GL4 Pipeline state for the rendering pipeline.
*/
class GL4PipelineState : public PipelineState {
public:
  GL4PipelineState();

  vvoid SetViewport(Viewport viewport) override { 
    SetDirty();
    m_viewport = viewport; 
  }

  vvoid SetBlendFunc(BlendFunc src, BlendFunc dst) override { 
    SetDirty();
    m_blendsrc = src;
    m_blenddst = dst; 
  }

  vvoid SetBlendEq(BlendEq eq) override { 
    SetDirty();
    m_blendeq = eq; 
  }

  vvoid SetBlendMode(vbool enable) override { 
    SetDirty();
    m_blend = enable; 
  }

  vvoid SetCullMode(vbool enable) override { 
    SetDirty();
    m_cull = enable; 
  }
  
  vvoid SetCullFace(CullFace face) override { 
    SetDirty();
    m_cullface = face; 
  }

  vvoid SetFrontFace(FrontFace face) override { 
    SetDirty();
    m_frontface = face; 
  }

  vvoid SetDepthMode(vbool enable) override { 
    SetDirty();
    m_depth = enable; 
  }

  vvoid SetDepthFunc(DepthFunc func) override {
    SetDirty();
    m_depthfunc = func;
  }

  vvoid Update() override;
  vbool NeedsUpdate() const override { return m_dirty; }

  vbool IsCulling() const override { return m_depth; }
  vbool IsBlending() const override { return m_blend; }
  vbool HasDepth() const override { return m_depth; }
  DepthFunc GetDepthFunc() const override { return m_depthfunc; }
  BlendEq GetBlendEquation() const override { return m_blendeq; }
  BlendFunc GetBlendFunctionSrc() const override { return m_blendsrc; }
  BlendFunc GetBlendFunctionDst() const override { return m_blenddst; }

  ShaderProgram *GetShaderProgram() const override { 
    return static_cast<ShaderProgram *>(program);
  }

  vvoid SetShaderProgram(ShaderProgram *prgm) override {
    if (program != prgm) {
      SetDirty();
      program = static_cast<GLSLShaderProgram *>(prgm);
    }
  }

  vvoid SetTopology(Topology topology) override {
    SetDirty(); 
    m_topology = topology; 
  }

  Topology GetTopology() const override { return m_topology; }

  Viewport GetViewport() const override { return m_viewport; }
  
  std::string GetName() const override { return name; }
  vvoid SetName(std::string name) override { this->name = name; }
  
private:

  vvoid SetDirty() { m_dirty = true; }
  vvoid SetClean() { m_dirty = false; }

  vbool m_blend             = false;
  BlendEq m_blendeq         = BlendEq::vikr_BLEND_ADD;
  BlendFunc m_blendsrc     = BlendFunc::vikr_BLEND_SRC_ALPHA;
  BlendFunc m_blenddst      = BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA;  

  vbool m_depth             = true;
  DepthFunc m_depthfunc     = DepthFunc::vikr_DEPTH_LESS;

  vbool m_cull              = true;
  CullFace m_cullface       = CullFace::vikr_BACK_FACE;
  FrontFace m_frontface     = FrontFace::vikr_COUNTER_CLOCKWISE;

  /*
    Is the pipeline state clean? Has anything been changed before?
  */
  vbool m_dirty             = false;

  Viewport m_viewport;

  Topology m_topology       = Topology::VIKR_TRIANGLES;

  /**
    Shaders linked in the pipeline.
  */
  std::map<ShaderStage, Shader *> shaders;

  GLSLShaderProgram *program;
  std::string name;
};
} // vikr
#endif // __VIKR_GL4_PIPELINE_STATE_HPP