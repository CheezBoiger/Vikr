//
// Copyright (c) Mario Garcia, Under the MIT License.
//
/**
  Our Framebuffer is the forefront of our Rendering API, sepcifically for 
  offscreen rendering. 
*/
#ifndef __VIKR_FRAMEBUFFER_HPP
#define __VIKR_FRAMEBUFFER_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/viewport.hpp>
#include <glm/glm.hpp>

#include <list>
#include <vector>

namespace vikr {


class Texture;
class RenderTarget;
class Renderbuffer;
class RenderPass;

struct Viewport;


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
  virtual vuint64 GetFramebufferId() = 0;

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
    Clear all attachments.
  */
  virtual vvoid ClearAttachments() = 0;

  /**
    Validates the Framebuffer, or Revalidates if color attachements have been reassigned.
  */
  virtual vvoid Update() = 0;

  /**
    Check if this framebuffer has depth and stencil.
  */
  virtual vbool HasDepthStencil() = 0;
  virtual vbool IsMultisampled() = 0;

  /**
    Readbuffer.
  */
  virtual vvoid Readbuffer(BufferMode mode) = 0;
  
  /**
    Writebuffer.
  */
  virtual vvoid Writebuffer(BufferMode mode) = 0;

  /**
    Cleanup the framebuffer, this will destroy the framebuffer.
  */
  virtual vvoid Cleanup() = 0;

  /**
    Set the RenderPass for this Framebuffer. BE SURE TO CALL UPDATE 
    IN ORDER TO UPLOAD THE NEW RENDERTARGETS FROM THIS RENDERPASS.
  */
  virtual vvoid SetRenderPass(RenderPass *pass) = 0;
  
  /**
    Get the RenderPass.
  */
  virtual RenderPass *GetRenderPass() = 0;

  /**
    Get the Viewport of this Framebuffer.
  */
  virtual Viewport GetViewport() = 0;
  
  /**
    Set the Viewport of this Framebuffer.
  */
  virtual vvoid SetViewport(const Viewport &viewport) = 0;

  /**
    Blits this Framebuffer to the specified destination framebuffer.
  */
  virtual vvoid BlitTo(Framebuffer *framebuffer) = 0;
};
} // vikr
#endif // __VIKR_FRAMEBUFFER_HPP