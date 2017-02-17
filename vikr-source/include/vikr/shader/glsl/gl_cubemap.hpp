//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL_CUBE_MAP_HPP
#define __VIKR_GL_CUBE_MAP_HPP


#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/glsl/gl_texture.hpp>

namespace vikr {


class GL4Cubemap : public Cubemap, public GLTexture {
public:

  GL4Cubemap();

  vvoid Load(std::vector<const vchar *> &faces_path) override;

  vuint32 GetNativeId() override { return id; }

  vint32 Finalize() override;

private:
  std::vector<const vchar *> m_faces;
};
} // vikr
#endif // __VIKR_GL_CUBE_MAP_HPP