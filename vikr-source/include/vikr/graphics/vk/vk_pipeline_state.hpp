//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_PIPELINE_STATE_HPP
#define __VIKR_VK_PIPELINE_STATE_HPP

#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


class Shader;
class SpvShader;
class SpvShaderProgram;


/**
  Vulkan Pipeline State 
*/
class VKPipelineState : public PipelineState {
public:
  VKPipelineState();

  vvoid SetViewport(Viewport viewport) override;
  vvoid SetBlendFunc(BlendFunc src, BlendFunc dst) override;
  vvoid SetBlendEq(BlendEq eq) override;
  vvoid SetBlendMode(vbool enable) override;
  vvoid SetDepthMode(vbool enable) override;
  vvoid SetDepthFunc(DepthFunc func) override;
  vvoid SetCullMode(vbool enable) override;
  vvoid SetCullFace(CullFace face) override;
  vvoid SetFrontFace(FrontFace face) override;
  vvoid SetTopology(Topology topology) override;
  
  Viewport GetViewport() const override;
  vvoid Update() override;
  
  vbool NeedsUpdate() const override;

  vbool IsCulling() const override;
  vbool IsBlending() const override;
  vbool HasDepth() const override;
  
  DepthFunc GetDepthFunc() const override;
  BlendEq GetBlendEquation() const override;
  BlendFunc GetBlendFunctionSrc() const override;
  BlendFunc GetBlendFunctionDst() const override;
  Topology GetTopology() const override;

  ShaderProgram *GetShaderProgram() const override;
  
  std::string GetName() const override;
  vvoid SetName(std::string name) override;

  vvoid Setup();

private:

  vvoid UpdateNativeViewport();
  vvoid UpdateNativeScissors();

  FrontFace m_frontface       = FrontFace::vikr_COUNTER_CLOCKWISE;
  CullFace m_cullface         = CullFace::vikr_BACK_FACE;
  Topology m_topology         = Topology::VIKR_TRIANGLES;

  /**
    Current Viewport State.
  */
  Viewport m_viewport;

  VkViewport m_native_viewport;
  VkRect2D m_native_scissor;

  vbool m_blend                 = false;
  BlendFunc m_blendsrc          = BlendFunc::vikr_BLEND_ONE;
  BlendFunc m_blenddst          = BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA;
  BlendEq m_blendeq             = BlendEq::vikr_BLEND_ADD;

  vbool m_depth                 = true;
  DepthFunc m_depthfunc         = DepthFunc::vikr_DEPTH_LESS;
  
  SpvShaderProgram *m_currProgram  = nullptr;

  VkMemoryManager<VkPipeline> m_pipeline;
  VkMemoryManager<VkPipelineLayout> m_pipelinelayout;

}; 
} // vikr
#endif // __VIKR_VK_PIPELINE_STATE_HPP
