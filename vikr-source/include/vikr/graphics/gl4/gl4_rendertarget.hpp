//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GL4_RENDERTARGET_HPP
#define __VIKR_GL4_RENDERTARGET_HPP


#include <vikr/graphics/render_target.hpp>


namespace vikr {


/**
  OpenGL Render Texture.
*/
class GL4RenderTexture : public RenderTexture {
public:
  GL4RenderTexture(std::string t_name, vuint32 width, vuint32 height, 
    vbool alpha, vbool multisampled, DataTypeFormat precision);

};


/**
  OpenGL Renderbuffer. 
*/
class GL4Renderbuffer : public Renderbuffer {
public:
  GL4Renderbuffer(vuint32 width, vuint32 height, vbool multisampled);
};


class GL4RenderDepthTexture : public RenderDepthTexture {
public:
  GL4RenderDepthTexture(std::string name, vuint32 width, vuint32 height, 
    vbool multisampled, DataTypeFormat precision);
};
} // vikr
#endif // __VIKR_GL4_RENDERTARGET_HPP