//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_PIPELINE_STATE_HPP
#define __VIKR_GL4_PIPELINE_STATE_HPP


#include <graphics/pipeline_state.hpp>


namespace vikr {


class GL4PipelineState : public PipelineState {
public:
  GL4PipelineState();
  
  
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
};
} // vikr
#endif // __VIKR_GL4_PIPELINE_STATE_HPP