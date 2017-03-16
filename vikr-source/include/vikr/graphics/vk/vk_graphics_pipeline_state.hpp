//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_PIPELINE_STATE_HPP
#define __VIKR_VK_PIPELINE_STATE_HPP

#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>
#include <vikr/graphics/graphics.hpp>


namespace vikr {


class Shader;
class SpvShader;
class SpvShaderProgram;
class VKRenderDevice;


/// Vulkan Graphics Pipeline State.
/// This pipeline is designed to bake in the pipeline
/// for use in rendering. OpenGL deals with a dynamic 
/// pipeline state, which is rather easy to use, but
/// doesn't offer the optimizations and power that Vulkan
/// offers in it's implementation.  
class VKGraphicsPipelineState : public GraphicsPipelineState {
public:
  VKGraphicsPipelineState();
  Viewport GetViewport() const override;
  Scissor2D GetScissor() const override;
  vbool IsCulling() const override;
  vbool IsBlending() const override;
  vbool HasDepth() const override;
  DepthCompare GetDepthCompare() const override;
  BlendEq GetBlendEquation() const override;
  BlendFactor GetBlendFactorSrc() const override;
  BlendFactor GetBlendFactorDst() const override;
  Topology GetTopology() const override;
  std::string GetName() const override;
  vvoid SetName(std::string name) override;
  vvoid Bake(GraphicsPipelineDescription &description) override;
  vvoid Setup();
  VkPipelineLayout GetPipelineLayout() { return m_pipelinelayout.Get(); }
  VkPipeline GetNativePipeline() { return m_pipeline; };

private:
  vvoid UpdateNativeViewport();
  vvoid UpdateNativeScissors();
  VKRenderDevice *device;
  VkFrontFace m_frontface         = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  VkCullModeFlagBits m_cullface   = VK_CULL_MODE_BACK_BIT;
  VkPrimitiveTopology m_topology  = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

  /// Current Viewport State.
  Viewport m_viewport;
  VkViewport m_native_viewport;
  VkRect2D m_native_scissor;
  vbool m_blend                     = false;
  VkBlendFactor m_blendsrc          = VK_BLEND_FACTOR_SRC_ALPHA;
  VkBlendFactor m_blenddst          = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  VkBlendOp m_blendeq               = VK_BLEND_OP_ADD;
  VkPolygonMode m_polygon           = VK_POLYGON_MODE_FILL;
  vbool m_depth                     = true;
  VkCompareOp m_depthfunc           = VK_COMPARE_OP_LESS;
  VkMemoryManager<VkPipeline> m_pipeline;
  VkMemoryManager<VkPipelineLayout> m_pipelinelayout;
}; 
} // vikr
#endif // __VIKR_VK_PIPELINE_STATE_HPP
