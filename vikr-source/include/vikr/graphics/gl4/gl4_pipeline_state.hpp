//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_PIPELINE_STATE_HPP
#define __VIKR_GL4_PIPELINE_STATE_HPP


#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/graphics/viewport.hpp>

#include <vikr/shader/shader.hpp>


namespace vikr {


class GL4PipelineState : public PipelineState {
public:
  GL4PipelineState();

  vvoid SetViewport(Viewport viewport) override {  }
  
  vvoid SetShader(Shader *shader) override { }

  vvoid SetBlendFunc(BlendFunc func) override { }

  vvoid SetBlendEq(BlendEq eq) override { }

  vvoid SetBlendMode(vbool enable) override { }

  vvoid SetCullMode(vbool enable) override { }
  
  vvoid SetCullFace(CullFace face) override { }

  vvoid SetFrontFace(FrontFace face) override { }

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
  
private:

  Shader *m_shader = nullptr;

  vbool m_blend;
  BlendEq m_blendeq;
  BlendFunc m_blendfunc;
  
  vbool m_depth;
  DepthFunc m_depthfunc;

  /*
    Is the pipeline state clean? Has anything been changed before?
  */
  vbool m_dirty;

  Viewport m_viewport;
};
} // vikr
#endif // __VIKR_GL4_PIPELINE_STATE_HPP