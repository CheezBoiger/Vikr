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
  RenderTarget(vuint32 width, vuint32 height, vbool has_depthstencil);

  virtual vvoid Generate() = 0;

  vvoid SetTexture(Texture *texture) { m_texture = texture; }
  vvoid SetWidth(vuint32 width) { m_width = width; }
  vvoid SetHeight(vuint32 height) { m_height = height; }

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }

  vbool HasDepthAndStencil() { return m_depthstencil; }
  vvoid SetHasDepthAndStencil(vbool depthstencil) { m_depthstencil = depthstencil; }

  Texture *GetTexture() { return m_texture; }
  std::vector<Texture *> *GetColorAttachments() { return &m_color_attachments; }

protected:

  vuint32 m_id;
  Texture *m_texture;
  vuint32 m_width;
  vuint32 m_height;  
  vbool m_depthstencil;

  std::vector<Texture *> m_color_attachments;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
