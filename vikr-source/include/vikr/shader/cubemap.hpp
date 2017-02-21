//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CUBEMAP_HPP
#define __VIKR_CUBEMAP_HPP


#include <vikr/shader/texture.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/shader/texture_config.hpp>
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

  /**
    Path to faces is optional.
  */
  virtual vvoid Load(std::vector<const vchar *> *face_paths) = 0;

  virtual vuint32 GetNativeId() = 0;

  virtual vvoid SetMagFilter(TextureFilterMode mode) = 0;

  virtual vvoid SetMinFilter(TextureFilterMode mode) = 0;

  virtual vvoid SetWrapS(TextureWrapMode mode) = 0;

  virtual vvoid SetWrapT(TextureWrapMode mode) = 0;

  virtual vvoid SetWrapR(TextureWrapMode mode) = 0;

  virtual vvoid OverrideFaceWidth(vuint32 val) = 0;
  
  virtual vvoid OverrideFaceHeight(vuint32 val) = 0;

  virtual vvoid ClearSizeOverride() = 0;
  
  virtual vvoid Cleanup() = 0;
};
} // vikr
#endif // __VIKR_CUBEMAP_HPP