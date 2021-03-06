//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE3D_HPP
#define __VIKR_GL_TEXTURE3D_HPP

#include <vikr/shader/glsl/gl_texture2d.hpp>

namespace vikr {



class GLTexture3D : public GLTexture2D {
public:
  GLTexture3D();
  GLTexture3D(vuint32 width, vuint32 height, vuint32 depth);

  vint32 Finalize() override;

  vint32 GetDepth() override { return m_depth; }
  vvoid SetDepth(vint32 depth) override { m_depth = depth; }

private:

  vint32 m_depth;
};
} // vikr
#endif // __VIKR_GL_TEXTURE3D_HPP