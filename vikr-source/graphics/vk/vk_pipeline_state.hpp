//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_PIPELINE_STATE_HPP
#define __VIKR_PIPELINE_STATE_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>

namespace vikr {


class Shader;


/**
  PipelineState describes the Rendering API graphics 
  pipeline. This determines the Rasterization state,
  fragment and vertex shaders, tessellation, polygon state,
  and others. It is mainly the configurations for debugging 
  and whatnot.
*/
VIKR_INTERFACE class PipelineState {
  VIKR_DISALLOW_COPY_AND_ASSIGN(PipelineState);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(PipelineState);
  PipelineState() { }
  virtual ~PipelineState() { }


  virtual vvoid EnableCullMode(vbool enable) = 0;
  virtual vvoid EnableBlendMode(vbool enable) = 0;
  virtual vvoid EnableWireframeMode(vbool enable) = 0;

  virtual vvoid SetShader(Shader *) = 0;
}; 
} // vikr
#endif // __VIKR_PIPELINE_STATE_HPP
