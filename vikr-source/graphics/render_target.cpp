//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#include <graphics/render_target.hpp>

namespace vikr {


RenderTarget::RenderTarget()
  : RenderTarget(0, 0)
{
}


RenderTarget::RenderTarget(vuint32 width, vuint32 height) 
  : m_width(width)
  , m_height(height)
  , m_texture(nullptr)
{
}


RenderTarget::~RenderTarget() 
{
}
} // vikr