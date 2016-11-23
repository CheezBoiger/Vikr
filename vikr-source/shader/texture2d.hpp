//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE2D_HPP
#define __VIKR_TEXTURE2D_HPP

#include <shader/texture.hpp>

namespace vikr {


class Texture2D : public Texture {
public:

protected:

  vuint32 width;
  vuint32 height;
};
} // vikr
#endif // __VIKR_TEXTURE2D_HPP