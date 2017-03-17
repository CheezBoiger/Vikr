//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_SPV_TEXTURE_1D_HPP
#define __VIKR_SPV_TEXTURE_1D_HPP


#include <vikr/shader/spv/spv_texture.hpp>


namespace vikr {


class SpvTexture1D : public SpvTexture {
public:
  virtual vint32 Finalize();

  virtual vint32 GetHeight() = 0;
  virtual vint32 GetDepth() = 0;
};
} // vikr
#endif // __VIKR_SPV_TEXTURE_1D_HPP