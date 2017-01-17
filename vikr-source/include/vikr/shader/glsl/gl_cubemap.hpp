//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL_CUBE_MAP_HPP
#define __VIKR_GL_CUBE_MAP_HPP


#include <vikr/shader/cubemap.hpp>


namespace vikr {


class GLCubemap : public Cubemap {
public:

  GLCubemap();

  vvoid Generate(std::vector<const vchar *> faces = std::vector<const vchar *>()) override;

};
} // vikr
#endif // __VIKR_GL_CUBE_MAP_HPP