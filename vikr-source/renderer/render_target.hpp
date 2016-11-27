//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/framebuffer.hpp>
#include <shader/texture.hpp>

#include <vector>

namespace vikr {


/**
  Render Target for post processing.
*/
class RenderTarget {
public:
  RenderTarget() : m_texture(nullptr) { }
  RenderTarget(vuint32 width, vuint32 height);

  virtual vvoid Generate() = 0;

  virtual vvoid BindDepthStencil() = 0;
  virtual vvoid BindTexture(vuint32 index) = 0;

  vvoid SetTexture(Texture *texture) { m_texture = texture; }
  vvoid SetWidth(vuint32 width) { m_width = width; }
  vvoid SetHeight(vuint32 height) { m_height = height; }

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }

  vbool HasDepthAndStencil() { return m_depthstencil; }

  Texture *GetTexture() { return m_texture; }
  std::vector<Texture *> *GetColorAttachments() { return &m_color_attachments; }

protected:

  vuint32 m_id                              = 0;
  vuint32 m_rbo                             = 0;
  Texture *m_texture                        = nullptr;
  vuint32 m_width                           = 0;
  vuint32 m_height                          = 0;  
  vbool m_depthstencil                      = false;

  std::vector<Texture *> m_color_attachments;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
