//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_context.hpp>
#include <vikr/graphics/gl4/gl4_commandbuffer.hpp>
#include <vikr/graphics/gl4/gl4_graphics_pipeline_state.hpp>
#include <vikr/graphics/gl4/gl4_renderpass.hpp>
#include <vikr/graphics/gl4/gl4_vertexbuffer.hpp>
#include <vikr/graphics/gl4/gl4_framebuffer.hpp>
#include <vikr/shader/glsl/gl4_cubemap.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/graphics_command.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/shader/material.hpp>

#include <vikr/shader/glsl/gl4_texture.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/shader/glsl/gl4_texture.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>

#include <vikr/input/window.hpp>



namespace vikr {

#define CLEAN_PIPELINE() { \
  if (m_currPipeline->NeedsUpdate()) { \
    m_currPipeline->Update(); \
  } \
}


GLenum GetGLTopology(Topology topology) {
  switch (topology) {
    case Topology::VIKR_LINES: return GL_LINES;
    case Topology::VIKR_TRIANGLES: return GL_TRIANGLES;
    case Topology::VIKR_POINTS: return GL_POINTS;
    case Topology::VIKR_TRIANGLE_FAN: return GL_TRIANGLE_FAN;
    case Topology::VIKR_LINE_STRIP: return GL_LINE_STRIP;
    case Topology::VIKR_TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
    default: return GL_TRIANGLES;  
  }
}


GL4RenderContext::GL4RenderContext()
{
  glEnable(GL_FRAMEBUFFER_SRGB);
  glEnable(GL_MULTISAMPLE);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


vvoid GL4RenderContext::Draw(vuint32 start, vuint32 vertices) {
  CLEAN_PIPELINE();
  glDrawArrays(
    GetGLTopology(m_currPipeline->GetTopology()), 
    start, 
    vertices
  );
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::DrawIndexed(const vvoid *indices, vuint32 elements) {
  CLEAN_PIPELINE();
  glDrawElements(
    GetGLTopology(m_currPipeline->GetTopology()),
    elements,
    GL_UNSIGNED_INT,
    indices
  );
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::SetTexture(Texture *texture, vuint32 index) {  
  CLEAN_PIPELINE();
  if (!texture) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Texture is null.");
    return;
  }
  GL4Texture *gl_texture = static_cast<GL4Texture *>(texture);
  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(gl_texture->GetNativeTarget(), gl_texture->GetNativeId());
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::SetRenderTarget(RenderTarget *target, vuint32 index) {
  CLEAN_PIPELINE();
  if (target) {
    switch (target->GetRenderType()) {
      case RenderTargetType::render_TEXTURE_MULTISAMPLE:
      case RenderTargetType::render_TEXTURE: {
        Texture *tex = static_cast<Texture *>(target->GetTexture());
        SetTexture(tex, index);
      }
      break;
      default: break;
    }
  }

  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::ChangeTopology(Topology topology) {
  m_currPipeline->SetTopology(topology);
}


vvoid GL4RenderContext::ChangeViewport(Viewport  *port) {
  m_currPipeline->SetViewport(*port);
}


vvoid GL4RenderContext::Clear() {
  CLEAN_PIPELINE();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


vvoid GL4RenderContext::SetCullFace(CullFace face) {
  m_currPipeline->SetCullFace(face);
}


vvoid GL4RenderContext::SetFrontFace(FrontFace face) {
  m_currPipeline->SetFrontFace(face);
}


vvoid GL4RenderContext::EnableBlendMode(vbool enable) {
  m_currPipeline->SetBlendMode(enable);
}


vvoid GL4RenderContext::EnableCullMode(vbool enable) {
  m_currPipeline->SetCullMode(enable);
}


vvoid GL4RenderContext::EnableDepthMode(vbool enable) {
  m_currPipeline->SetDepthMode(enable);
}


vvoid GL4RenderContext::SetBlendEq(BlendEq eq) {
  m_currPipeline->SetBlendEq(eq);
}


vvoid GL4RenderContext::SetBlendMode(BlendFunc src, BlendFunc dst) {
  m_currPipeline->SetBlendFunc(src, dst);
}


vvoid GL4RenderContext::SetDepthFunc(DepthFunc func) {
  m_currPipeline->SetDepthFunc(func);
}


vvoid GL4RenderContext::ClearWithColor(glm::vec4 color) {
  CLEAN_PIPELINE();
  glClearColor(color.x, color.y, color.z, color.w);
}


vvoid GL4RenderContext::ExecuteCommands(CommandbufferList *commandbuffer) {
  CLEAN_PIPELINE();
  if (commandbuffer) {
    GL4CommandbufferList *list = static_cast<GL4CommandbufferList *>(commandbuffer);
    for (Commandbuffer *command : list->Raw()) {
      VIKR_ASSERT(command);
      static_cast<GL4Commandbuffer *>(command)->Execute(this);
    }
  }
}


vvoid GL4RenderContext::SetFramebuffer(Framebuffer *framebuffer) {
  CLEAN_PIPELINE();
  if (framebuffer) {
    GL4Framebuffer *glFb = static_cast<GL4Framebuffer *>(framebuffer);
    glFb->Bind();
    Clear();
  } else {
    // Set back to default.
    Viewport default_port = { 
      0, 0, 
      Window::GetMainWindow()->GetWidth(), 
      Window::GetMainWindow()->GetHeight() 
    };
    m_currPipeline->SetViewport(default_port);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Clear();
  }

  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::SetShaderUniforms(ShaderUniformParams *params) {
  CLEAN_PIPELINE();
  if (!params) { 
    return;
  }
  vuint32 shader_program = 0;
  /*
    TODO(): Will need to parse these location values in the future.
  */
  //VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(glGetError()));
  shader_program = static_cast<GLSLShaderProgram *>(m_currPipeline->GetShaderProgram())->GetNativeId();
  if (params->uniforms) {
    for (auto variable = params->uniforms->begin(); variable != params->uniforms->end(); ++variable) {
      std::string s = variable->first;
      switch(variable->second.type) {
      case vikr_UNIFORM_BOOL: 
        glProgramUniform1i(shader_program, 
          glGetUniformLocation(shader_program, variable->first.c_str()), 
          (vint32)variable->second.m_bool); 
      break;
      case vikr_UNIFORM_INT: 
        glProgramUniform1i(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          variable->second.m_integer); 
      break;
      case vikr_UNIFORM_VEC2: 
        glProgramUniform2fv(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          1, 
          glm::value_ptr(variable->second.m_vec2)); 
      break;
      case vikr_UNIFORM_VEC3: 
        glProgramUniform3fv(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          1, 
          glm::value_ptr(variable->second.m_vec3)); 
      break;
      case vikr_UNIFORM_VEC4: 
        glProgramUniform4fv(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          1, 
          glm::value_ptr(variable->second.m_vec4));
      break;
      case vikr_UNIFORM_MAT2: 
        glProgramUniformMatrix2fv(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          1, 
          GL_FALSE, 
          glm::value_ptr(variable->second.m_mat2));
      break;
      case vikr_UNIFORM_MAT3: 
        glProgramUniformMatrix3fv(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          1, 
          GL_FALSE, 
          glm::value_ptr(variable->second.m_mat3)); 
      break;
      case vikr_UNIFORM_MAT4: 
        glProgramUniformMatrix4fv(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          1, 
          GL_FALSE, 
          glm::value_ptr(variable->second.m_mat4));
      break;
      case vikr_UNIFORM_DOUBLE: 
        glProgramUniform1d(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          variable->second.m_double);
      break;
      case vikr_UNIFORM_FLOAT: 
        glProgramUniform1f(shader_program,
          glGetUniformLocation(shader_program, variable->first.c_str()),
          variable->second.m_float);
      break;
      default: break;
      }
      VIKR_ASSERT(glGetError() == 0);
    }
  }

  ClearTextures();
  // Bind all texture that was given.
  if (params->samplers) {
    m_currTextures.reserve(params->samplers->size());
    for(auto sampler = params->samplers->begin(); sampler != params->samplers->end(); ++sampler) {
      if (sampler->second.type != vikr_UNIFORM_SAMPLERCUBE) {
        GL4Texture *texture = static_cast<GL4Texture *>(sampler->second.texture);
        SetTexture(texture, sampler->second.i);
        m_currTextures.push_back(std::move(sampler->second));
      } else {
        GL4Cubemap *cubemap = static_cast<GL4Cubemap *>(sampler->second.cubemap);
        SetTexture(cubemap, sampler->second.i);
      }
    }
  }
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::ClearTextures() {
  // clear previous textures.
  for (vuint32 i = 0; i < m_currTextures.size(); ++i) {
    GL4Texture *tex = static_cast<GL4Texture *>(m_currTextures[i].texture);
    glActiveTexture(GL_TEXTURE0 + m_currTextures[i].i);
    glBindTexture(tex->GetNativeTarget(), 0);
    VIKR_ASSERT(glGetError() == 0);
  }
  m_currTextures.clear();
}


vvoid GL4RenderContext::QueryVertexbuffer(Vertexbuffer *buffer) {
  CLEAN_PIPELINE();
  if (buffer) {
    GL4Vertexbuffer *buf = static_cast<GL4Vertexbuffer *>(buffer);
    glBindVertexArray(static_cast<vuint32>(buf->GetVertexArrayId()));
    m_queriedVertexbuffer = buf;
  }
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::Present() {
  glfwSwapBuffers(Window::GetMainWindow()->GetWindow());
  VIKR_ASSERT(glGetError() == 0);
}


GraphicsPipelineState *GL4RenderContext::GetGraphicsPipelineState() {
  return static_cast<GraphicsPipelineState *>(m_currPipeline);
}


vvoid GL4RenderContext::BeginRecord(Commandbuffer *buf) {
  m_recordCommandbuffer = static_cast<GL4Commandbuffer *>(buf);
}


vvoid GL4RenderContext::EndRecord() {
  m_recordCommandbuffer = nullptr;
}

vvoid GL4RenderContext::ApplyGraphicsPipelineState(GraphicsPipelineState *pipelinestate) {
  if (pipelinestate == m_currPipeline) {
    return;
  }
  m_currPipeline = static_cast<GL4GraphicsPipelineState *>(pipelinestate);
  m_currPipeline->Update();
}


Framebuffer *GL4RenderContext::GetFramebuffer() {
  return static_cast<Framebuffer *>(m_currFramebuffer);
}


vvoid GL4RenderContext::SetMaterial(Material *material) {
  ShaderUniformParams params;
  params.uniforms = material->GetMaterialValues();
  params.samplers = material->GetUniformSamplers();
  SetShaderUniforms(&params);
}


vvoid GL4RenderContext::Dispatch(vuint32 x, vuint32 y, vuint32 z) {
}


vvoid GL4RenderContext::SetRenderPass(RenderPass *pass) {
}
} // vikr