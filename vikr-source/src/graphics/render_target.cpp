//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <vikr/graphics/render_target.hpp>

namespace vikr {


RenderTarget::RenderTarget(GraphicsPipeline pipeline
  , vuint32 width
  , vuint32 height
  , vbool alpha
  , vbool multisampled
  , RenderTargetType type)
    : m_targetType(type)
    , alpha(alpha)
    , m_pipeline(pipeline)
    , m_width(width)
    , m_height(height)
    , multisampled(multisampled)
{
}


RenderTexture::RenderTexture(GraphicsPipeline pipeline, 
  vuint32 width, vuint32 height, vbool alpha, vbool multisampled)
  : RenderTarget(pipeline, width, height, alpha, multisampled, render_TEXTURE)
{
}


Renderbuffer::Renderbuffer(GraphicsPipeline pipeline, vuint32 width, 
  vuint32 height, vbool multisampled)
  : RenderTarget(pipeline, width, height, false, multisampled, render_RENDERBUFFER)
{
}


RenderDepthTexture::RenderDepthTexture(GraphicsPipeline pipeline, vuint32 width, 
  vuint32 height, vbool multisampled)
  : RenderTarget(pipeline, width, height, false, multisampled, render_DEPTH_TEXTURE)
{
}
} // vikr