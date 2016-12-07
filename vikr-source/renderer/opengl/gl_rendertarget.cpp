//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/opengl/gl_rendertarget.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


/**
  This will likely fall into it's own resources class. Needs to be handled by
  Material.
*/
GLenum GLRenderTarget::GetDepthFunct(DepthFunc funct) {
  switch(funct) {
  case DepthFunc::vikr_DEPTH_ALWAYS:    return GL_ALWAYS;
  case DepthFunc::vikr_DEPTH_EQUAL:     return GL_EQUAL;
  case DepthFunc::vikr_DEPTH_GEQUAL:    return GL_GEQUAL;
  case DepthFunc::vikr_DEPTH_GREATER:   return GL_GREATER;
  case DepthFunc::vikr_DEPTH_LEQUAL:    return GL_LEQUAL;
  case DepthFunc::vikr_DEPTH_LESS:      return GL_LESS;
  case DepthFunc::vikr_DEPTH_NEVER:     return GL_NEVER;
  case DepthFunc::vikr_DEPTH_NOTEQUAL:  return GL_NOTEQUAL;
  default:                              return GL_LESS;
  }
}

/**
  These need to go into Material! Waste of time searching!
*/
GLenum GLRenderTarget::GetBlendFunct(BlendFunc blend) {
  switch(blend) {
  case BlendFunc::vikr_BLEND_CONSTANT_ALPHA:              return GL_CONSTANT_ALPHA;
  case BlendFunc::vikr_BLEND_CONSTANT_COLOR:              return GL_CONSTANT_COLOR;
  case BlendFunc::vikr_BLEND_DST_ALPHA:                   return GL_DST_ALPHA;
  case BlendFunc::vikr_BLEND_DST_COLOR:                   return GL_DST_COLOR;
  case BlendFunc::vikr_BLEND_GL_ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
  case BlendFunc::vikr_BLEND_ONE:                         return GL_ONE;
  case BlendFunc::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR:    return GL_ONE_MINUS_CONSTANT_COLOR;
  case BlendFunc::vikr_BLEND_ONE_MINUS_DST_ALPHA:         return GL_ONE_MINUS_DST_ALPHA;
  case BlendFunc::vikr_BLEND_ONE_MINUS_DST_COLOR:         return GL_ONE_MINUS_DST_COLOR;
  case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA:         return GL_ONE_MINUS_SRC1_ALPHA;
  case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_COLOR:         return GL_ONE_MINUS_SRC_COLOR;
  case BlendFunc::vikr_BLEND_SRC_ALPHA:                   return GL_SRC_ALPHA;
  case BlendFunc::vikr_BLEND_SRC_COLOR:                   return GL_SRC_COLOR;
  case BlendFunc::vikr_BLEND_ZERO:                        return GL_ZERO;
  default:                                                return GL_ZERO;
  }
}


GLenum GLRenderTarget::GetBlendEq(BlendEq eq) {
  switch (eq) {
    case BlendEq::vikr_BLEND_ADD:               return GL_FUNC_ADD;
    case BlendEq::vikr_BLEND_REVERSE_SUBTRACT:  return GL_FUNC_REVERSE_SUBTRACT;
    case BlendEq::vikr_BLEND_SUBTRACT:          return GL_FUNC_SUBTRACT;
    default:                                    return GL_FUNC_ADD;
  }
}


GLenum GLRenderTarget::GetFrontFace(FrontFace mode) {
  switch(mode) {
  case FrontFace::vikr_CLOCKWISE:                       return GL_CW;
  case FrontFace::vikr_COUNTER_CLOCKWISE:               return GL_CCW;
  default:                                              return GL_CCW;
  }
}


GLenum GLRenderTarget::GetCullFace(CullFace face) {
  switch(face) {
  case CullFace::vikr_FRONT_FACE:                       return GL_FRONT;
  case CullFace::vikr_BACK_FACE:                        return GL_BACK;
  default:                                              return GL_BACK;
  }
}


GLRenderTarget::GLRenderTarget()
{
}


GLRenderTarget::GLRenderTarget(vuint32 width, vuint32 height)
  : RenderTarget(width, height)
{
}


vvoid GLRenderTarget::Generate() {
  if (!m_texture) {
    GLTexture2D texture(m_width, m_height);
    texture.SetWidth(m_width);
    texture.SetFilterMin(TextureFilterMode::vikr_TEXTURE_LINEAR);
    texture.SetFormat(TextureFormat::vikr_RGB);
    texture.SetInternalFormat(TextureFormat::vikr_RGB);
    texture.SetMipmapping(false);
    texture.Create(0);
    m_texture = std::make_unique<GLTexture2D>(std::move(texture));
  }

  if (!m_rbo) {
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, VIKR_DEPTH24_STENCIL8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
  }
}


vvoid GLRenderTarget::BindDepthStencil() {
  if (m_rbo) {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    m_depthstencil = true;
  }
}


vvoid GLRenderTarget::SetBlendDst(BlendFunc funct) {
  m_blendDst = funct;
  native_blendDst = GetBlendFunct(funct);
}


vvoid GLRenderTarget::SetDepthFunc(DepthFunc funct) {
  m_depthFunc = funct;
  native_depthFunc = GetDepthFunct(funct);
}


vvoid GLRenderTarget::SetBlendSrc(BlendFunc funct) {
  m_blendSrc = funct;
  native_blendSrc = GetBlendFunct(funct);
}


vvoid GLRenderTarget::SetBlendEq(BlendEq eq) {
  m_blendEq = eq;
  native_blendEq = GetBlendEq(eq);
}


vvoid GLRenderTarget::SetCullFace(CullFace face) {
  m_cullFace = face;
  native_cullFace = GetCullFace(face);
}


vvoid GLRenderTarget::SetFrontFace(FrontFace face) {
  m_frontFace = face;
  native_frontFace = GetFrontFace(face);
}
} // vikr