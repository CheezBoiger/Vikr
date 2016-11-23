//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE1D_HPP
#define __VIKR_TEXTURE1D_HPP

#include <shader/texture.hpp>

namespace vikr {


class Texture1D : public Texture {
public:

protected:
  vuint32 width;
};
} // vikr
#endif // __VIKR_TEXTURE1D_HPP