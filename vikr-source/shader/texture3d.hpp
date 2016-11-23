//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE3D_HPP
#define __VIKR_TEXTURE3D_HPP

#include <shader/texture.hpp>

namespace vikr {


class Texture3D : public Texture {
public:

protected:

  vuint32 width;
  vuint32 height;
  vuint32 depth;
};
} // vikr
#endif // __VIKR_TEXTURE3D_HPP