//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GL4_RENDERTARGET_HPP
#define __VIKR_GL4_RENDERTARGET_HPP


#include <graphics/render_target.hpp>


namespace vikr {


/**
  OpenGL Render Texture.
*/
class GL4RenderTexture : public RenderTexture {
public:
  GL4RenderTexture(std::string t_name, vuint32 width, vuint32 height, 
    vbool alpha, DataTypeFormat precision);

};


/**
  OpenGL Renderbuffer. 
*/
class GL4Renderbuffer : public Renderbuffer {
public:
  GL4Renderbuffer(vuint32 width, vuint32 height);
};
} // vikr
#endif // __VIKR_GL4_RENDERTARGET_HPP