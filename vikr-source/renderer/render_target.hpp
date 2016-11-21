//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_TARGET_HPP
#define __VIKR_RENDER_TARGET_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/framebuffer.hpp>


namespace vikr {


class Texture;


/**
  Render Target for post processing.
*/
class RenderTarget {
public:


  vvoid SetTexture(Texture *texture) { m_texture = texture; }
  vvoid SetWidth(vuint32 width) { m_width = width; }
  vvoid SetHeight(vuint32 height) { m_height = height; }

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }

  vbool HasDepthAndStencil() { return depthstencil; }

  Texture *GetTexture() { return m_texture; }
private:
  Texture *m_texture;
  vuint32 m_width;
  vuint32 m_height;  
  vbool depthstencil;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
