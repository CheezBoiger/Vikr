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
#include <memory>

namespace vikr {


/**
  Render Target for post processing. This is an abstract class
  designed as a plugin for rendering APIs.

  OpenGL: Associates this object with GLRenderTarget.
  Vulkan: Associates this obejct with VKRenderTarget.
*/
class RenderTarget {
public:
  RenderTarget() : m_texture(nullptr) { }
  RenderTarget(vuint32 width, vuint32 height);

  virtual vvoid Generate() = 0;

  virtual vvoid BindDepthStencil() = 0;
  virtual vvoid BindTexture(vuint32 index) = 0;
  virtual vvoid Unbind() = 0;
  virtual vvoid Bind() = 0;

  vvoid SetWidth(vuint32 width) { m_width = width; }
  vvoid SetHeight(vuint32 height) { m_height = height; }

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }

  vbool HasDepthAndStencil() { return m_depthstencil; }

  Texture *GetTexture() { return m_texture.get(); }
  std::vector<Texture *> *GetColorAttachments() { return &m_color_attachments; }

  vvoid SetClearColor(glm::vec3 cl) { clearcolor = cl; }
  glm::vec3 GetClearColor() { return clearcolor; }

  virtual vbool IsComplete() = 0;

protected:

  glm::vec3 clearcolor                      = glm::vec3(0.1f, 0.1f, 0.1f);
  vuint32 m_fbo                             = 0;
  vuint32 m_rbo                             = 0;
  std::unique_ptr<Texture> m_texture        = nullptr;
  vuint32 m_width                           = 0;
  vuint32 m_height                          = 0;  
  vbool m_depthstencil                      = false;

  std::vector<Texture *> m_color_attachments;
};
} // vikr
#endif // __VIKR_RENDER_TARGET_HPP
