//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_SPV_TEXTURE_2D_HPP
#define __VIKR_SPV_TEXTURE_2D_HPP


#include <vikr/shader/spv/spv_texture_1d.hpp>


namespace vikr {


class SpvTexture2D : public SpvTexture1D {
public:

  virtual vint32 Finalize() override;

  vint32 GetHeight() override { return m_height; }
  virtual vint32 GetDepth() override = 0;
private:
  vint32 m_height;
};
} // vikr
#endif // __VIKR_SPV_TEXTURE_2D_HPP