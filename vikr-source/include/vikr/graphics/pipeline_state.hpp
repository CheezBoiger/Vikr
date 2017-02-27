//
// Copyright (c) Mario Garcia, Under the MIT License.
//
/**
  PipelineState holds all information regarding the current pipeline
  that has been configured for the Render API. This Object holds all
  shaders (vertex, fragment/pixel, compute, tesselation, hull, etc shaders),
  depth mode, cull mode, blending equations, and what not. we keep track of our
  pipeline state through this object for organizational reasons.
*/
#ifndef __VIKR_PIPELINE_STATE_HPP
#define __VIKR_PIPELINE_STATE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <vikr/graphics/stencildepth.hpp>
#include <vikr/graphics/topology.hpp>

#include <vikr/shader/shader.hpp>
#include <vikr/shader/shader_program.hpp>


namespace vikr {


class Shader;
struct Viewport;


/**
  Pipeline state defines the current state of the Renderer API.
  This is an interface for both Vulkan and OpenGL use.
*/
class PipelineState : public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(PipelineState);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(PipelineState);
  PipelineState() { }
  virtual ~PipelineState() { }

  /**
    Set the viewport for the context.
  */
  virtual vvoid SetViewport(Viewport viewport) = 0;

  /**
    Set the blending function.
  */
  virtual vvoid SetBlendFunc(BlendFunc src, BlendFunc dst) = 0;

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
    Set the Depth function.
  */
  virtual vvoid SetDepthFunc(DepthFunc func) = 0;
  
  /**
    Set the Cull mode.
  */
  virtual vvoid SetCullMode(vbool enable) = 0;

  /**
    Set the Cull Face.
  */
  virtual vvoid SetCullFace(CullFace face) = 0;

  /**
    Set the Front Face.
  */
  virtual vvoid SetFrontFace(FrontFace face) = 0;

  virtual vvoid SetTopology(Topology topology) = 0;

  /**
    Viewport stuff.
  */
  virtual Viewport GetViewport() const = 0;

  /*
    Update the Pipeline State
  */
  virtual vvoid Update() = 0;

  /*
    Check if the PipelineState needs to be updated.
  */
  virtual vbool NeedsUpdate() const = 0;

  virtual vbool IsCulling() const = 0;
  virtual vbool IsBlending() const = 0;
  virtual vbool HasDepth() const = 0;
  virtual DepthFunc GetDepthFunc() const = 0;
  virtual BlendEq GetBlendEquation() const = 0;
  virtual BlendFunc GetBlendFunctionSrc() const = 0;
  virtual BlendFunc GetBlendFunctionDst() const = 0;
  virtual Topology GetTopology() const = 0;

  virtual vvoid SetShaderProgram(ShaderProgram *prgm) = 0;

  virtual ShaderProgram *GetShaderProgram() const = 0;

  virtual std::string GetName() const = 0;
  virtual vvoid SetName(std::string name) = 0;
};
} // vikr
#endif // __VIKR_PIPELINE_STATE_HPP