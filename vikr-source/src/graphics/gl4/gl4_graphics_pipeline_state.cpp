//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_graphics_pipeline_state.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>

#include <vikr/input/window.hpp>


namespace vikr {


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


GL4GraphicsPipelineState::GL4GraphicsPipelineState()
  : program(nullptr)
{
  m_viewport = {
    0,
    0,
    Window::GetMainWindow()->GetWidth(),
    Window::GetMainWindow()->GetHeight()
  };
}

vvoid GL4GraphicsPipelineState::Update() {
  if (!m_dirty) {
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, 
      "Nothing to configure for pipeline state, skipping...");
    return;
  }

  glViewport(
    m_viewport.win_x,
    m_viewport.win_y,
    m_viewport.win_width,
    m_viewport.win_height
  );

  if (m_blend) {
    glEnable(GL_BLEND);
  } else {
    glDisable(GL_BLEND);
  }
  
  glBlendEquation(GetGLBlendEq(m_blendeq));
  glBlendFunc(GetGLBlendMode(m_blendsrc), GetGLBlendMode(m_blenddst));
  glDepthFunc(GetGLDepthFunc(m_depthfunc));

  if (m_depth) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }

  if (m_cull) {
    glEnable(GL_CULL_FACE);
    GLenum t;
    switch (m_frontface) {
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
    switch (m_cullface) {
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
  } else {
    glDisable(GL_CULL_FACE);
  }

  if (program) {
    glUseProgram(program->GetNativeId());
  }

  /**
    Everything looks clean.
  */
  SetClean();
}
} // vikr