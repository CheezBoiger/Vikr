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
#include <vikr/shader/glsl/glsl_program.hpp>

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
  DepthCompare GetDepthFunc() const override;
  BlendEq GetBlendEquation() const override;
  BlendFunc GetBlendFunctionSrc() const override;
  BlendFunc GetBlendFunctionDst() const override;
  Topology GetTopology() const override;
  Viewport GetViewport() const override { return m_viewport; }
  Scissor2D GetScissor() const override { return m_scissor; }
  std::string GetName() const override { return name; }
  vvoid SetName(std::string name) override { this->name = name; }
  vvoid Bake(GraphicsPipelineDescription &description) override;

  GLuint GetNativeBlendEq() { return m_blendeq; }
  GLuint GetNativeBlendSrc() { return m_blendsrc; }
  GLuint GetNativeBlendDst() { return m_blenddst; }
  GLuint GetNativeDepthFunc() { return m_depthfunc; }
  GLuint GetNativeCullFace() { return m_cullface; }
  GLuint GetNativeFrontFace() { return m_frontface; }

private:
  vvoid SetDirty() { m_dirty = true; }
  vvoid SetClean() { m_dirty = false; }

  vbool m_blend             = false;
  GLuint m_blendeq          = GL_FUNC_ADD;
  GLuint m_blendsrc         = GL_SRC_ALPHA;
  GLuint m_blenddst         = GL_ONE_MINUS_SRC_ALPHA;  

  vbool m_depth             = true;
  GLuint m_depthfunc        = GL_LESS;

  vbool m_cull              = true;
  GLuint m_cullface         = GL_BACK;
  GLuint m_frontface        = GL_CCW;

  /*
    Is the pipeline state clean? Has anything been changed before?
  */
  vbool m_dirty             = false;

  Viewport m_viewport;

  GLuint m_topology         = GL_TRIANGLES;
  Scissor2D m_scissor;

  /**
    Shaders linked in the pipeline.
  */
  std::map<ShaderStage, Shader *> shaders;

  GLSLShaderProgram *program;
  std::string name;
};
} // vikr
#endif // __VIKR_GL4_PIPELINE_STATE_HPP