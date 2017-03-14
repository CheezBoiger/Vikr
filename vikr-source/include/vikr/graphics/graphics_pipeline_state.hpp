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
class Uniformbuffer;
class Texture;
class RenderDevice;


/// Dynamic state information.
enum DynamicStateInfo {
  vikr_DYNAMIC_STATE_VIEWPORT,
  vikr_DYNAMIC_STATE_SCISSOR,
  vikr_DYNAMIC_STATE_BLEND_CONSTANTS,
  vikr_DYNAMIC_STATE_DEPTH_BIAS
};


/// Graphics Pipeline description. Since we are going the way of 
/// Vulkan, we want to keep the paradigm similar, so as to 
/// give the most performance for the programmer.
struct GraphicsPipelineDescription {
  /// Describe the viewport for the Graphics Pipeline.
  Viewport viewport;
  
  /// Describe the scissor cutoff for the Viewport.
  Scissor2D scissor;

  /// Describe the Blending functionality to use for
  /// this Graphics Pipelinestate. 
  BlendFunc bsrc, bdst;

  /// The Blend equation for this Graphics pipelinestate.
  /// This value is normally kept to vikr_BLEND_ADD, as it
  /// is the default blending equation.
  BlendEq beq;

  /// The Depth function used to compare Renderables in the 
  /// zbuffer. 
  DepthCompare dfunct;
  CullFace cull;
  FrontFace front;
  Topology topology;
  PolygonMode polygon;
  vbool blend;
  vbool depth;
  vbool culling;
  std::vector<Shader *> m_shaders;
   
  /// Dynamic states describe dynamic values to be 
  /// manually defined by the program for every
  /// Pipeline binding within a command buffer.
  /// An empty dynamic static buffer will prevent 
  /// having to manually input values for every bind,
  /// but it will also prevent the availablility of 
  /// a dynamic pipeline state, which will require 
  /// having to create another pipeline state to 
  /// deal with, say, blend/depth operations.
  std::vector<DynamicStateInfo> m_dynamicstates;
};


/// Pipeline state defines the current state of the Renderer API.
/// This is an interface for both Vulkan and OpenGL use.
class GraphicsPipelineState : public RenderDeviceObject, public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(GraphicsPipelineState);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GraphicsPipelineState);
  GraphicsPipelineState(GraphicsAPIType type) 
    : RenderDeviceObject(type) { }
  virtual ~GraphicsPipelineState() { }

  /// Get the Viewport for this pipeline state. 
  /// This viewport defines the layout resolution of 
  /// the screen, depending on what these values are, in 
  /// pixels.
  virtual Viewport GetViewport() const = 0;

  /// Get the Scissor viewport of this pipeline state.
  virtual Scissor2D GetScissor() const = 0;

  virtual vbool IsCulling() const = 0;
  virtual vbool IsBlending() const = 0;
  virtual vbool HasDepth() const = 0;
  virtual DepthCompare GetDepthFunc() const = 0;
  virtual BlendEq GetBlendEquation() const = 0;
  virtual BlendFunc GetBlendFunctionSrc() const = 0;
  virtual BlendFunc GetBlendFunctionDst() const = 0;
  virtual Topology GetTopology() const = 0;

  virtual vvoid Bake(GraphicsPipelineDescription &description) = 0;

  virtual GraphicsPipelineState *CreateChild() = 0;
  
  virtual std::string GetName() const = 0;
  virtual vvoid SetName(std::string name) = 0;
};
} // vikr
#endif // __VIKR_PIPELINE_STATE_HPP