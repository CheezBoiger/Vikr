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
#include <vikr/shader/glsl/glsl_material.hpp>
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


GL4RenderContext::GL4RenderContext()
{
  glEnable(GL_FRAMEBUFFER_SRGB);
  glEnable(GL_MULTISAMPLE);
  VIKR_ASSERT(glGetError() == 0);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


vvoid GL4RenderContext::Draw(GL4Commandbuffer *buffer, vuint32 start, vuint32 vertices, vuint32 instances) {
  auto execute = [=] (vuint32 start, vuint32 vertices, vuint32 instances) -> vvoid {
    if (instances == 0) {
      glDrawArrays(
        m_currPipeline->GetNativeTopology(),
        start,
        vertices
      );
    } else {
      glDrawArraysInstanced(
        m_currPipeline->GetNativeTopology(),
        start, 
        vertices,
        instances
      );
    }
    VIKR_ASSERT(glGetError() == 0);
  };
  buffer->AddCommand([=] () -> vvoid { execute(start, vertices, instances); });
}


vvoid GL4RenderContext::DrawIndexed(GL4Commandbuffer *buffer, const vvoid *indices, vuint32 elements, vuint32 instances) {
  auto execute = [=] (const vvoid *indices, vuint32 elements, vuint32 instances) -> vvoid {
    if (instances == 0) {
      glDrawElements(
        m_currPipeline->GetNativeTopology(),
        elements,
        GL_UNSIGNED_INT,
        indices
      );
    } else {
      glDrawElementsInstanced(
        m_currPipeline->GetNativeTopology(),
        elements,
        GL_UNSIGNED_INT,  
        indices,
        instances
      );
    }
    VIKR_ASSERT(glGetError() == 0);
  };
  buffer->AddCommand([=] ( ) -> vvoid { execute(indices, elements, instances); });
}


vvoid GL4RenderContext::SetTexture(Texture *texture, vuint32 index) {  
  if (!texture) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Texture is null.");
    return;
  }
  GL4Texture *gl_texture = static_cast<GL4Texture *>(texture);
  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(gl_texture->GetNativeTarget(), gl_texture->GetNativeId());
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::Clear(GL4Commandbuffer *buffer) {
  buffer->AddCommand( [=] ( ) -> vvoid {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  });
}


vvoid GL4RenderContext::ClearWithColor(GL4Commandbuffer *buffer, glm::vec4 color) {
  auto execute = [=] (glm::vec4 color) -> vvoid {
    glClearColor(color.x, color.y, color.z, color.w);
  };
  buffer->AddCommand([=] ( ) -> vvoid { execute(color); });
}


vvoid GL4RenderContext::SetFramebuffer(Framebuffer *framebuffer) {
  if (framebuffer) {
    GL4Framebuffer *glFb = static_cast<GL4Framebuffer *>(framebuffer);
    glFb->Bind();
    if (glFb->GetViewport().win_height != 0 || glFb->GetViewport().win_width != 0) {
      glViewport(
        glFb->GetViewport().win_x,
        glFb->GetViewport().win_y,
        glFb->GetViewport().win_width,
        glFb->GetViewport().win_height
      );
    }
  } else {
    // Set back to default.
    Viewport default_port = { 
      0, 0, 
      Window::GetMainWindow()->GetWidth(), 
      Window::GetMainWindow()->GetHeight() 
    };
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  VIKR_ASSERT(glGetError() == 0);
}


vvoid GL4RenderContext::SetShaderUniforms(ShaderUniformParams *params) {
  if (!params) { 
    return;
  }
  vuint32 shader_program = 0;
  /*
    TODO(): Will need to parse these location values in the future.
  */
  //VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(glGetError()));
  shader_program = m_currPipeline->GetShaderProgram();
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


vvoid GL4RenderContext::QueryVertexbuffer(GL4Commandbuffer *commandbuffer, Vertexbuffer *buffer) {
  auto execute = [=] (Vertexbuffer *buffer) -> vvoid {
    if (buffer) {
      GL4Vertexbuffer *buf = static_cast<GL4Vertexbuffer *>(buffer);
      glBindVertexArray(static_cast<vuint32>(buf->GetVertexArrayId()));
      m_queriedVertexbuffer = buf;
    }
    VIKR_ASSERT(glGetError() == 0);
  };
  commandbuffer->AddCommand([=] () -> vvoid { execute(buffer); });
}


GraphicsPipelineState *GL4RenderContext::GetGraphicsPipelineState() 
{
  return static_cast<GraphicsPipelineState *>(m_currPipeline);
}


vvoid GL4RenderContext::BindGraphicsPipelineState(GL4Commandbuffer *buffer, GraphicsPipelineState *pipelinestate) 
{
  auto execute = [=] (GraphicsPipelineState *pipelinestate) -> vvoid {
    if (pipelinestate == m_currPipeline) {
      return;
    }
    m_currPipeline = static_cast<GL4GraphicsPipelineState *>(pipelinestate);
    if (m_currPipeline->IsBlending()) {
      glEnable(GL_BLEND);
      glBlendEquation(m_currPipeline->GetNativeBlendEq);
      glBlendFunc(m_currPipeline->GetNativeBlendSrc(), m_currPipeline->GetNativeBlendDst());
    } else {
      glDisable(GL_BLEND);
    }

    if (m_currPipeline->IsCulling()) {
      glEnable(GL_CULL_FACE); 
      glCullFace(m_currPipeline->GetNativeCullFace());
      glFrontFace(m_currPipeline->GetNativeFrontFace());
    } else {
      glDisable(GL_CULL_FACE);
    }

    if (m_currPipeline->HasDepth()) {
      glEnable(GL_DEPTH);
      glDepthFunc(m_currPipeline->GetNativeDepthFunc());
    } else {
      glDisable(GL_DEPTH);
    }

    glViewport(
      m_currPipeline->GetViewport().win_x,
      m_currPipeline->GetViewport().win_y,
      m_currPipeline->GetViewport().win_width,
      m_currPipeline->GetViewport().win_height
    );
    glScissor(
      m_currPipeline->GetScissor().offsetx,
      m_currPipeline->GetScissor().offsety,
      m_currPipeline->GetScissor().width,
      m_currPipeline->GetScissor().height
    );
    
  };
  buffer->AddCommand([=] () -> vvoid { execute(pipelinestate); });
}


vvoid GL4RenderContext::BindComputePipelineState(GL4Commandbuffer *buffer, ComputePipelineState *pipeline)
{
  auto execute = [=] (ComputePipelineState *pipeline) -> vvoid {
    
  };
  buffer->AddCommand([=] ( ) -> vvoid { execute(pipeline); });
}


Framebuffer *GL4RenderContext::GetFramebuffer() 
{
  return static_cast<Framebuffer *>(m_currFramebuffer);
}


vvoid GL4RenderContext::SetMaterial(GL4Commandbuffer *buffer, Material *material) 
{
  if (material->GetAPIType() != vikr_API_OPENGL) {
    return;
  }
  GLSLMaterial *gl_material = static_cast<GLSLMaterial *>(material);
  ShaderUniformParams params;
  params.uniforms = gl_material->GetMaterialValues();
  params.samplers = gl_material->GetUniformSamplers();
  SetShaderUniforms(&params);
}


vvoid GL4RenderContext::Dispatch(GL4Commandbuffer *buffer, vuint32 x, vuint32 y, vuint32 z) 
{
}


vvoid GL4RenderContext::SetRenderPass(GL4Commandbuffer *buffer, RenderPass *pass) 
{
}
} // vikr