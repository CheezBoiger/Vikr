//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GL4_RENDERTARGET_HPP
#define __VIKR_GL4_RENDERTARGET_HPP


#include <graphics/render_target.hpp>


namespace vikr {


/**
  Going to need to redo this program.
*/
class GL4RenderTexture : public RenderTexture {
public:
  GL4RenderTexture(vuint32 width, vuint32 height, vbool alpha, DataTypeFormat precision);

};


class GL4Renderbuffer : public Renderbuffer {
public:
  GL4Renderbuffer(vuint32 width, vuint32 height);
};
} // vikr
#endif // __VIKR_GL4_RENDERTARGET_HPP