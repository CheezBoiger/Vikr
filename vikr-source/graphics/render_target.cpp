//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <graphics/render_target.hpp>

namespace vikr {


RenderTarget::RenderTarget(GraphicsPipeline pipeline
  , vuint32 width
  , vuint32 height
  , vbool alpha
  ,  RenderTargetType type)
    : m_targetType(type)
    , alpha(alpha)
    , m_pipeline(pipeline)
    , m_width(width)
    , m_height(height)
{
}


RenderTexture::RenderTexture(GraphicsPipeline pipeline, 
  vuint32 width, vuint32 height, vbool alpha)
  : RenderTarget(pipeline, width, height, alpha, render_TEXTURE)
{
}


Renderbuffer::Renderbuffer(GraphicsPipeline pipeline, vuint32 width, vuint32 height)
  : RenderTarget(pipeline, width, height, false, render_RENDERBUFFER)
{
}


RenderDepthTexture::RenderDepthTexture(GraphicsPipeline pipeline, vuint32 width, 
  vuint32 height)
  : RenderTarget(pipeline, width, height, false, render_DEPTH_TEXTURE)
{
}
} // vikr