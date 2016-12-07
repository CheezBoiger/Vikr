//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <renderer/render_target.hpp>

namespace vikr {


RenderTarget::RenderTarget()
  : RenderTarget(0, 0)
{
}


RenderTarget::RenderTarget(vuint32 width, vuint32 height) 
  : m_width(width)
  , m_height(height)
  , m_texture(nullptr)
{
  SetDepthFunc(m_depthFunc);
  SetBlendSrc(m_blendSrc);
  SetBlendDst(m_blendDst);
  SetCullFace(m_cullFace);
  SetFrontFace(m_frontFace);
  SetBlendEq(m_blendEq);
}


RenderTarget::~RenderTarget() 
{
  if (m_rbo) {
    glDeleteRenderbuffers(1, &m_rbo);
  }
}
} // vikr