//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_PIPELINE_STATE_HPP
#define __VIKR_VK_PIPELINE_STATE_HPP

#include <vikr/graphics/pipeline_state.hpp>


namespace vikr {


class Shader;


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

private:

}; 
} // vikr
#endif // __VIKR_VK_PIPELINE_STATE_HPP
