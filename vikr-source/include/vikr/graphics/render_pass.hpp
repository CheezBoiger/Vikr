//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERPASS_HPP
#define __VIKR_RENDERPASS_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/viewport.hpp>
#include <vikr/util/vikr_log.hpp>

#include <vector>


namespace vikr {


class Framebuffer;



enum AttachmentRefType {
  vikr_ATTACHMENT_COLOR,
  vikr_ATTACHMENT_DEPTH,
  vikr_ATTACHMENT_DEPTH_STENCIL
};


/// Aliasing sampling.
enum SampleCount {
  vikr_SAMPLE_1_BIT,
  vikr_SAMPLE_2_BIT,
  vikr_SAMPLE_4_BIT,
  vikr_SAMPLE_8_BIT,
  vikr_SAMPLE_16_BIT,
  vikr_SAMPLE_32_BIT
};


struct AttachmentDescription {
  AttachmentRefType ref;
  ImageFormat       format;
  SampleCount       samples;
  vuint32           attachment;
};


class Subpass {
public:
  /// Add an attachment reference to the RenderPass. Attachment references tell
  /// the Framebuffer which attachments are which (color, depth, stencil, etc).
  vvoid AddAttachmentDescription(AttachmentRefType ref, vuint32 pAttachment);

  /// Remove an Attachment reference. Returns true if an attachment reference
  /// was successfully removed. False if no attachment was found.
  vbool RemoveAttachmentDescription(vuint32 pAttachment);

  /// Get an attachment reference from the specified index.
  AttachmentRefType GetAttachmentDescription(vuint32 pAttachment);
  
private:
  std::vector<AttachmentRefType> attachmentsRefs;
};


/// Controls passes that are sent to the Renderer. These RenderPasses
/// are what render within a framebuffer for offscreen rendering.
///
/// TODO(): RenderPass Needs to hold ONLY Attachments References, used by the Framebuffer
///         to determine which Textures (Images) attach to where (color, depth, stencil, etc).
class RenderPass : public RenderDeviceObject, public GUID {
public:
  RenderPass(GraphicsAPIType type)  
    : RenderDeviceObject(type) { }
  /// Polymorphic Renderpass destructor.
  virtual ~RenderPass() { }

  virtual vvoid SetSubpass(Subpass &subpass) = 0;

  /// Generate the RenderPass object. This is inclined toward Vulkan, and is
  /// meant to provide descriptions that will aid the Framebuffer in figuring
  /// out how to handle the Texture/ImageViews upon rendering.
  virtual vvoid Generate() = 0;


  /// Update the RenderPass.
  virtual vvoid Update() = 0;
  
  /// Cleanup the Renderpass, if need be.
  virtual vvoid Cleanup() = 0;

  virtual Framebuffer *GetFramebuffer() = 0;
  virtual vvoid SetFramebuffer(Framebuffer *buffer) = 0;
};
} // vikr
#endif // __VIKR_RENDERPASS_HPP