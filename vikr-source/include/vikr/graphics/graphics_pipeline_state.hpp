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
#include <vikr/graphics/viewport.hpp>
#include <vikr/graphics/render_device.hpp>

#include <vikr/shader/shader_config.hpp>


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
  BlendFactor bsrc, bdst;

  /// The Blend equation for this Graphics pipelinestate.
  /// This value is normally kept to vikr_BLEND_ADD, as it
  /// is the default blending equation.
  BlendEq beq;

  /// The Depth function used to compare Renderables in the 
  /// zbuffer. 
  DepthCompare dcompare;

  /// Cull Mode description. Determine face culling for the
  /// back, front, or both. 
  CullFace cull;

  /// Determine the winding order of how meshes render on the screen.
  FrontFace front;

  /// Determine the topology of the pipeline. The default would be 
  /// triangle tesselation.
  Topology topology;
  
  /// Polygon mode determines how to render meshes, by line, solid
  /// coloring, or simply wireframe...
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

  /// Check if this pipeline is culling.
  virtual vbool IsCulling() const = 0;

  /// Check if this pipeline is blending.
  virtual vbool IsBlending() const = 0;

  /// Determine if this pipeline has depth for 3D support.
  virtual vbool HasDepth() const = 0;

  /// Get the Depth compare function used in this pipeline.
  virtual DepthCompare GetDepthCompare() const = 0;

  /// Get the Blend equation used in this pipeline.
  virtual BlendEq GetBlendEquation() const = 0;

  /// Get the Blend factor for the src.
  virtual BlendFactor GetBlendFactorSrc() const = 0;

  /// Get the Blend Factor for the destination.
  virtual BlendFactor GetBlendFactorDst() const = 0;

  /// Get the topology of the pipeline state.
  virtual Topology GetTopology() const = 0;

  /// Get a Shader that was baked into this pipeline state.
  /// Returns reference to the Shader that is in this pipeline.
  /// Returns nullptr if now shader was found with requested 
  /// shader stage.
  virtual Shader *GetShader(ShaderStage stage) = 0;

  /// Bake descriptions into the pipeline state. Once baked, the pipeline
  /// can no longer be updated, or changed. Be sure to describe the pipeline
  /// state with the Graphics Pipeline description, as it will be a way
  /// to create pipelines for the renderer.
  virtual vvoid Bake(GraphicsPipelineDescription &description) = 0;

  /// Create a child from this Parent PipelineState. Child is created, provided with
  /// an empty graphics description object, which will be filled with information about 
  /// the parent pipeline. If Parent pipeline state can not be derived, then a nullptr
  /// will be returned, along with no info about the parent state.
  virtual GraphicsPipelineState *CreateChild(GraphicsPipelineDescription &inherited) = 0;
  
  virtual std::string GetName() const = 0;
  virtual vvoid SetName(std::string name) = 0;
};
} // vikr
#endif // __VIKR_PIPELINE_STATE_HPP