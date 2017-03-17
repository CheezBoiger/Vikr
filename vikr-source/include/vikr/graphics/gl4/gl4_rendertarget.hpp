//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GL4_RENDERTARGET_HPP
#define __VIKR_GL4_RENDERTARGET_HPP


#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/graphics.hpp>

#include <memory>


namespace vikr {


/// Render Target image for GL4Framebuffer.
class GL4RenderTarget : public RenderTarget {
  //VIKR_DISALLOW_COPY_AND_ASSIGN(GL4RenderTarget);
public:
  GL4RenderTarget(RenderTargetType type)
    : RenderTarget(type)
  { }

  GL4RenderTarget(GL4RenderTarget &&s)
    : RenderTarget(s.GetRenderTargetType())
  {
  }

  GL4RenderTarget &operator=(GL4RenderTarget &&s)
  {
    return *this;
  }

  vvoid SetFormat(ImageFormat format) override;
  ImageFormat GetFormat() override;
  vvoid Finalize() override;

  vuint32 GetWidth() override { return m_width; }
  vuint32 GetHeight() override { return m_height; }
  vvoid SetWidth(vuint32 width) override { m_width = width; }
  vvoid SetHeight(vuint32 height) override { m_height = height; }
  GLuint GetNativeRenderTargetId() { return target_id; }
  GLenum GetNativeBaseFormat() { return native_base_format; }
  GLenum GetNativeInternalFormat() { return native_internal_format; }
  GLenum GetNativeDatatypeFormat() { return native_datatype_format; }

protected:
  GLuint target_id;  
  vuint32 m_width;
  vuint32 m_height;
  GLenum native_base_format;
  GLenum native_internal_format;
  GLenum native_datatype_format;
};
} // vikr
#endif // __VIKR_GL4_RENDERTARGET_HPP