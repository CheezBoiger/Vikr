//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_context.hpp>
#include <graphics/gl4/gl4_vertexbuffer.hpp>
#include <graphics/command_buffer.hpp>
#include <graphics/graphics_command.hpp>
#include <graphics/render_pass.hpp>
#include <graphics/render_target.hpp>
#include <graphics/framebuffer.hpp>
#include <graphics/pipeline_state.hpp>

#include <shader/glsl/gl_texture.hpp>
#include <shader/shader_uniform_params.hpp>
#include <shader/glsl/gl_texture.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <util/vikr_log.hpp>

#include <input/window.hpp>



namespace vikr {


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


GLenum GetGLBlendMode(BlendFunc func) {
  switch (func) {
    case BlendFunc::vikr_BLEND_CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;  
    case BlendFunc::vikr_BLEND_CONSTANT_COLOR: return GL_CONSTANT_COLOR;
    case BlendFunc::vikr_BLEND_DST_ALPHA: return GL_DST_ALPHA;
    case BlendFunc::vikr_BLEND_DST_COLOR: return GL_DST_COLOR;
    case BlendFunc::vikr_BLEND_GL_ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
    case BlendFunc::vikr_BLEND_ONE: return GL_ONE;
    case BlendFunc::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;  
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunc::vikr_BLEND_SRC_ALPHA: return GL_SRC_ALPHA;
    case BlendFunc::vikr_BLEND_SRC_COLOR: return GL_SRC_COLOR;
    case BlendFunc::vikr_BLEND_ZERO: return GL_ZERO;
    default: return GL_ONE_MINUS_CONSTANT_ALPHA;
  }
}


GLenum GetGLDepthFunc(DepthFunc mode) {
  switch (mode) {
    case DepthFunc::vikr_DEPTH_ALWAYS: return GL_ALWAYS;
    case DepthFunc::vikr_DEPTH_EQUAL: return GL_EQUAL;
    case DepthFunc::vikr_DEPTH_GEQUAL: return GL_GEQUAL;
    case DepthFunc::vikr_DEPTH_GREATER: return GL_GREATER;
    case DepthFunc::vikr_DEPTH_LEQUAL: return GL_LEQUAL;
    case DepthFunc::vikr_DEPTH_LESS: return GL_LESS;
    case DepthFunc::vikr_DEPTH_NEVER: return GL_NEVER;
    case DepthFunc::vikr_DEPTH_NOTEQUAL: return GL_NOTEQUAL;
    default: return GL_LESS;  
  }
}


GLenum GetGLBlendEq(BlendEq eq) {
  switch (eq) {
    case BlendEq::vikr_BLEND_ADD: return GL_FUNC_ADD;
    case BlendEq::vikr_BLEND_REVERSE_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT;
    case BlendEq::vikr_BLEND_SUBTRACT: return GL_FUNC_SUBTRACT;
    default: return GL_FUNC_ADD;
  }
}


GL4RenderContext::GL4RenderContext()
{
}


vvoid GL4RenderContext::Draw(vuint32 start, vuint32 vertices) {
  glDrawArrays(
    GetGLTopology(m_currTopology), 
    start, 
    vertices);
}


vvoid GL4RenderContext::DrawIndexed(const vvoid *indices, vuint32 elements) {
  glDrawElements(
    GetGLTopology(m_currTopology),
    elements,
    GL_UNSIGNED_INT,
    indices);
}


vvoid GL4RenderContext::SetTexture(Texture *texture, vuint32 index) {
  GLTexture *tex = static_cast<GLTexture *>(texture);  
  if (texture) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(tex->GetNativeTarget(), tex->GetNativeId());
  }
}


vvoid GL4RenderContext::SetRenderTarget(RenderTarget *target, vuint32 index) {
  if (target) {
  }
}


vvoid GL4RenderContext::ChangeTopology(Topology topology) {
  m_currTopology = topology;
}


vvoid GL4RenderContext::ChangeViewport(Viewport  *port) {
  if (port) {
    glViewport(
      port->win_x,
      port->win_y,
      port->win_width,
      port->win_height);
  }
}


vvoid GL4RenderContext::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


vvoid GL4RenderContext::SetCullFace(CullFace face) {
  GLenum t;
  switch (face) {
    case CullFace::vikr_FRONT_FACE:
      t = GL_FRONT;
    break;
    case CullFace::vikr_BACK_FACE:
      t = GL_BACK;
    break;
    default:
      t = GL_BACK;  
    break;  
  }
  glCullFace(t);
}


vvoid GL4RenderContext::SetFrontFace(FrontFace face) {
  GLenum t;
  switch (face) {
    case FrontFace::vikr_CLOCKWISE:
      t = GL_CW;
    break;
    case FrontFace::vikr_COUNTER_CLOCKWISE:
      t = GL_CCW;
    break;
    default:
      t = GL_CCW;
    break;
  }
  glFrontFace(t);
}


vvoid GL4RenderContext::EnableBlendMode(vbool enable) {
  if (enable) {
    glEnable(GL_BLEND);
  } else {
    glDisable(GL_BLEND);
  }
}


vvoid GL4RenderContext::EnableCullMode(vbool enable) {
  if (enable) {
    glEnable(GL_CULL_FACE);
  } else {
    glDisable(GL_CULL_FACE);
  }
}


vvoid GL4RenderContext::EnableDepthMode(vbool enable) {
  if (enable) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}


vvoid GL4RenderContext::SetBlendEq(BlendEq eq) {
  glBlendEquation(GetGLBlendEq(eq));
}


vvoid GL4RenderContext::SetBlendMode(BlendFunc src, BlendFunc dst) {
  glBlendFunc(GetGLBlendMode(src), GetGLBlendMode(dst));
}


vvoid GL4RenderContext::SetDepthFunc(DepthFunc func) {
  glDepthFunc(GetGLDepthFunc(func));
}


vvoid GL4RenderContext::ClearWithColor(glm::vec4 color) {
  glClearColor(color.x, color.y, color.z, color.w);
}


vvoid GL4RenderContext::ExecuteCommands(Commandbuffer *commandbuffer) {
  if (commandbuffer) {
    for (std::unique_ptr<GraphicsCommand> &command : commandbuffer->GetCommands()) {
      command->Execute(this);
    }
  }
}


vvoid GL4RenderContext::ConfigurePipelineState(PipelineState *state) {
}


vvoid GL4RenderContext::SetRenderPass(RenderPass *pass) {
  if (pass) {
    pass->Bind();
    Clear();
    ClearWithColor(glm::vec4(pass->ClearColor, 1.0f));
  } else {
    // Set back to default.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Clear();
  }
}


vvoid GL4RenderContext::SetShaderUniforms(ShaderUniformParams *params) {
  if (!params || !params->uniforms) { 
    return;
  }
  /*
    TODO(): Will need to parse these location values in the future.
  */
  //VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(glGetError()));

  for(auto variable : *params->uniforms) {
    std::string s = variable.first;
    switch(variable.second.type) {
    case vikr_BOOL: 
      glProgramUniform1i(m_currShaderProgram, 
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()), 
        (vint32)variable.second.m_bool); 
    break;
    case vikr_INT: 
      glProgramUniform1i(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        variable.second.m_integer); 
    break;
    case vikr_VEC2: 
      glProgramUniform2fv(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        1, 
        glm::value_ptr(variable.second.m_vec2)); 
    break;
    case vikr_VEC3: 
      glProgramUniform3fv(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        1, 
        glm::value_ptr(variable.second.m_vec3)); 
    break;
    case vikr_VEC4: 
      glProgramUniform4fv(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        1, 
        glm::value_ptr(variable.second.m_vec4));
    break;
    case vikr_MAT2: 
      glProgramUniformMatrix2fv(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        1, 
        GL_FALSE, 
        glm::value_ptr(variable.second.m_mat2));
    break;
    case vikr_MAT3: 
      glProgramUniformMatrix3fv(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        1, 
        GL_FALSE, 
        glm::value_ptr(variable.second.m_mat3)); 
    break;
    case vikr_MAT4: 
      glProgramUniformMatrix4fv(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        1, 
        GL_FALSE, 
        glm::value_ptr(variable.second.m_mat4));
    break;
    case vikr_DOUBLE: 
      glProgramUniform1d(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        variable.second.m_double);
    break;
    case vikr_FLOAT: 
      glProgramUniform1f(m_currShaderProgram,
        glGetUniformLocation(m_currShaderProgram, variable.first.c_str()),
        variable.second.m_float);
    break;
    default: break;
    }
  }
  // Bind all texture that was given.
  if (params->samplers) {
    for(auto sampler : *params->samplers) {
      SetTexture(sampler.second.texture, sampler.second.i);
    }
  }
}


vvoid GL4RenderContext::ApplyShaderProgram(vuint32 program_id) {
  if (program_id) {
    glUseProgram(program_id);
    m_currShaderProgram = program_id;
  }
}


vvoid GL4RenderContext::QueryVertexbuffer(Vertexbuffer *buffer) {
  if (buffer) {
    GL4Vertexbuffer *buf = static_cast<GL4Vertexbuffer *>(buffer);
    glBindVertexArray(buf->GetVertexArrayId());
    
  }
}


vvoid GL4RenderContext::Present() {
  glfwSwapBuffers(Window::GetMainWindow());
}
} // vikr