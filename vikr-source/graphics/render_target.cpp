//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <graphics/render_target.hpp>

namespace vikr {


RenderTarget::RenderTarget(GraphicsPipeline pipeline
  , vuint32 width
  , vuint32 height
  ,  RenderTargetType type)
    : m_targetType(type)
    , m_pipeline(pipeline)
    , m_width(width)
    , m_height(height)
{
}


RenderTexture::RenderTexture(GraphicsPipeline pipeline, vuint32 width, vuint32 height)
  : RenderTarget(pipeline, width, height, render_TEXTURE)
{
}


Renderbuffer::Renderbuffer(GraphicsPipeline pipeline, vuint32 width, vuint32 height)
  : RenderTarget(pipeline, width, height, render_RENDERBUFFER)
{
}
} // vikr