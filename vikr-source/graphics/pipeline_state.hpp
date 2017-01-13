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


class Shader;
struct Viewport;


/**
  Pipeline state defines the current state of the Renderer API.
  This is abstract for both Vulkan and OpenGL use.
*/
class PipelineState {
  VIKR_DISALLOW_COPY_AND_ASSIGN(PipelineState);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(PipelineState);
  virtual ~PipelineState() { }

  /**
    Set the viewport for the context.
  */
  virtual vvoid SetViewport(Viewport viewport) = 0;
  
  /**
    Set the shader for the pipeline state.
  */
  virtual vvoid SetShader(Shader *shader) = 0;

  /**
    Set the blending function.
  */
  virtual vvoid SetBlendFunc(BlendFunc func) = 0;

  /**
    Set the Blend equation.
  */
  virtual vvoid SetBlendEq(BlendEq eq) = 0;
  
  /**
    Set the Blend Mode.
  */
  virtual vvoid SetBlendMode(vbool enable) = 0;

  /**
    Set the Depth mode.
  */
  virtual vvoid SetDepthMode(vbool enable) = 0;
  
  /**
    Set the Cull mode.
  */
  virtual vvoid SetCullMode(vbool enable) = 0;

  /**
    Set the Cull Face.
  */
  virtual vbool SetCullFace(CullFace face) = 0;

  /**
    Set the Front Face.
  */
  virtual vvoid SetFrontFace(FrontFace face) = 0;
  

  /*
    Grab a specific pipeline shader stage.
  */
  virtual vuint32 GetVertexShader() = 0;
  virtual vuint32 GetFragmentShader() = 0;
  virtual vuint32 GetComputeShader() = 0;
  virtual vuint32 GetGeometryShader() = 0;

  virtual Viewport GetViewport() = 0;
  virtual Shader *GetShader() = 0;

  /*
    Update the Pipeline State
  */
  virtual vvoid Update() = 0;

  /*
    Check if the PipelineState needs to be updated.
  */
  virtual vbool NeedsUpdate() = 0;
};
} // vikr
#endif // __VIKR_PIPELINE_STATE_HPP