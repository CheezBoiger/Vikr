//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_PIPELINE_STATE_HPP
#define __VIKR_GL4_PIPELINE_STATE_HPP


#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/graphics/topology.hpp>

#include <vikr/shader/shader.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/shader/glsl/glsl_shader.hpp>

#include <map>
#include <string>


namespace vikr {



/// The GL4 Pipeline state for the rendering pipeline.
class GL4GraphicsPipelineState : public GraphicsPipelineState {
public:
  GL4GraphicsPipelineState();

  vbool IsCulling() const override { return m_cull; }
  vbool IsBlending() const override { return m_blend; }
  vbool HasDepth() const override { return m_depth; }
  DepthCompare GetDepthCompare() const override;
  BlendEq GetBlendEquation() const override;
  BlendFactor GetBlendFactorSrc() const override;
  BlendFactor GetBlendFactorDst() const override;
  Topology GetTopology() const override;
  Viewport GetViewport() const override { return m_viewport; }
  Scissor2D GetScissor() const override { return m_scissor; }
  std::string GetName() const override { return name; }
  vvoid SetName(std::string name) override { this->name = name; }
  vvoid Bake(GraphicsPipelineDescription &description) override;

  GraphicsPipelineState *CreateChild(GraphicsPipelineDescription &inherited) override;

  GLenum GetNativeBlendEq() { return m_blendeq; }
  GLenum GetNativeBlendSrc() { return m_blendsrc; }
  GLenum GetNativeBlendDst() { return m_blenddst; }
  GLenum GetNativeDepthFunc() { return m_depthCompare; }
  GLenum GetNativeCullFace() { return m_cullface; }
  GLenum GetNativeFrontFace() { return m_frontface; }
  GLenum GetNativeTopology() { return m_topology; }

  GLuint GetShaderProgram() { return m_shaderProgram; }
  Shader *GetShader(ShaderStage stage) override;

private:

  GLuint m_shaderProgram;
  vbool m_blend             = false;
  GLenum m_blendeq          = GL_FUNC_ADD;
  GLenum m_blendsrc         = GL_SRC_ALPHA;
  GLenum m_blenddst         = GL_ONE_MINUS_SRC_ALPHA;  

  vbool m_depth             = true;
  GLenum m_depthCompare     = GL_LESS;

  vbool m_cull              = true;
  GLenum m_cullface         = GL_BACK;
  GLenum m_frontface        = GL_CCW;

  Viewport m_viewport;

  GLenum m_topology         = GL_TRIANGLES;
  GLenum m_polygon          = GL_FILL;
  Scissor2D m_scissor;

  /**
    Shaders linked in the pipeline.
  */
  std::map<ShaderStage, GLSLShader *> shaders;
  std::vector<DynamicStateInfo>       dynamicinfo;
  std::string name;
};
} // vikr
#endif // __VIKR_GL4_PIPELINE_STATE_HPP