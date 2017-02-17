//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CUBEMAP_HPP
#define __VIKR_CUBEMAP_HPP


#include <vikr/shader/texture.hpp>
#include <vikr/graphics/render_device.hpp>
#include <memory>
#include <vector>


namespace vikr {


/**
  Render a cubemap 
*/
class Cubemap {
public:
  Cubemap() { }
  virtual ~Cubemap() { }

  virtual vvoid Load(std::vector<const vchar *> &faces_path) = 0;

  virtual vuint32 GetNativeId() = 0;

};
} // vikr
#endif // __VIKR_CUBEMAP_HPP