//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GL_TEXTURE3D_HPP
#define __VIKR_GL_TEXTURE3D_HPP

#include <vikr/shader/glsl/gl4_texture2d.hpp>

namespace vikr {



class GL4Texture3D : public GL4Texture2D {
public:
  GL4Texture3D();
  GL4Texture3D(vuint32 width, vuint32 height, vuint32 depth);

  vint32 Finalize() override;

  vint32 GetDepth() override { return m_depth; }
  vvoid SetDepth(vint32 depth) override { m_depth = depth; }

private:

  vint32 m_depth;
};
} // vikr
#endif // __VIKR_GL_TEXTURE3D_HPP