//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_PIPELINE_STATE_HPP
#define __VIKR_GL4_PIPELINE_STATE_HPP


#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/graphics/topology.hpp>

#include <vikr/shader/shader.hpp>


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
  
  vvoid SetShader(Shader *shader) override {
    SetDirty(); 
    m_shader = shader; 
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

  vuint32 GetVertexShader() const override {
    if (m_shader) {
      return m_shader->GetVertId();
    }
    return -1;
  }

  vuint32 GetFragmentShader() const override {
    if (m_shader) {
      return m_shader->GetFragId();
    }
    return -1;
  }

  vuint32 GetComputeShader() const override {
    if (m_shader) {
      return m_shader->GetCompId();
    }
    return -1;
  }

  vuint32 GetGeometryShader() const override {
    if (m_shader) {
      return m_shader->GetGeomId();
    }
    return -1;
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

  vuint32 GetShaderProgram() const override { 
    if (m_shader) {
      return m_shader->GetProgramId();
    }
    return -1;
  }

  vvoid SetTopology(Topology topology) override {
    SetDirty(); 
    m_topology = topology; 
  }

  Topology GetTopology() const override { return m_topology; }

  Shader *GetShader() const override { return m_shader; }

  Viewport GetViewport() const override { return m_viewport; }
  
  
private:

  vvoid SetDirty() { m_dirty = true; }
  vvoid SetClean() { m_dirty = false; }

  Shader *m_shader = nullptr;

  vbool m_blend             = false;
  BlendEq m_blendeq         = BlendEq::vikr_BLEND_ADD;
  BlendFunc m_blendsrc     = BlendFunc::vikr_BLEND_ONE;
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
};
} // vikr
#endif // __VIKR_GL4_PIPELINE_STATE_HPP