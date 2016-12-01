//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CUBEMAP_HPP
#define __VIKR_CUBEMAP_HPP

#include <shader/texture.hpp>
#include <memory>

namespace vikr {


class Cubemap {
public:
  
  
protected:
  std::unique_ptr<Texture> texture      = nullptr;
};
} // vikr
#endif // __VIKR_CUBEMAP_HPP