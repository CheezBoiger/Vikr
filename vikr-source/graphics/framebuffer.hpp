//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_FRAMEBUFFER_HPP
#define __VIKR_FRAMEBUFFER_HPP

#include <platform/vikr_types.hpp>
#include <glm/glm.hpp>

#include <list>

namespace vikr {


class Texture;
class RenderTarget;
class Renderbuffer;


enum class BufferMode {
  BUFFER_NONE,
  BUFFER_FRONT_LEFT,
  BUFFER_FRONT_RIGHT,
  BUFFER_BACK_LEFT,
  BUFFER_BACK_RIGHT,
  BUFFER_FRONT,
  BUFFER_BACK,
  BUFFER_LEFT,
  BUFFER_RIGHT
};


/**
  Framebuffer abstract. Used to be derived specifically for our Renderers.
  Alittle scary, Vulkan already contains a Framebuffer object for us to use.
  We will use this class to wrap it...

  Allowing Multi RenderPasses requires that we blit a src Framebuffer with a 
  destination Framebuffer, this can cause some performance penalties.

  OpenGL: Associates GLFramebuffer
  Vulkan: Associates VKFramebuffer
*/
class Framebuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(vikr::Framebuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(vikr::Framebuffer);
  virtual ~Framebuffer() { }
  Framebuffer() { }
  
  /** 
    Generate the Framebuffer with this function call.
  */
  virtual vvoid Generate() = 0;  

  
  /**
    Set the clear color of the Framebuffer. 
  */
  virtual vvoid SetClearColor(glm::vec3 color) = 0;
  
  /**
    Get the clear color of the Framebuffer. 
  */
  virtual glm::vec3 GetClearColor() = 0;
  
  /**
    Get the Framebuffer id.
  */
  virtual vuint32 GetFramebufferId() = 0;

  /**
    Check if this framebuffer is completely structure for use.
  */
  virtual vint32 IsComplete() = 0;

  /**
    Bind the framebuffer.
  */
  virtual vvoid Bind() = 0;

  /**
    Unbind the framebuffer.
  */
  virtual vvoid Unbind() = 0;

  /**
    Clear the depth
  */
  virtual vvoid ClearDepthStencil() = 0;


  /**
    Clear Color attachments from the Framebuffer.
  */
  virtual vvoid ClearTexture(vuint32 attachment) = 0;

  
  /**
    Bind a Render target to the Framebuffer.
  */
  virtual vvoid BindTexture(RenderTarget *target, vuint32 attachment) = 0;

  /**
    Bind a Depth component to the Framebuffer.
  */
  virtual vvoid BindDepthStencilBuffer(Renderbuffer *rbo) = 0;

  /**
    Destroy the framebuffer.
  */
  virtual vvoid DestroyFramebuffer() = 0;

  /**
    Get the color attachments from the framebuffer.
  */
  virtual std::vector<Texture *> *GetColorAttachments() = 0;

  /**
    Validates the Framebuffer, or Revalidates if color attachements have been reassigned.
  */
  virtual vvoid Validate() = 0;

  /**
    Check if this framebuffer has depth and stencil.
  */
  virtual vint32 HasDepthStencil() = 0;
  virtual vint32 IsMultisampled() = 0;

  virtual vvoid Readbuffer(BufferMode mode) = 0;
  virtual vvoid Writebuffer(BufferMode mode) = 0;
};
} // vikr
#endif // __VIKR_FRAMEBUFFER_HPP