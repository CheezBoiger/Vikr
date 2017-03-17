//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_SPV_TEXTURE_3D_HPP
#define __VIKR_SPV_TEXTURE_3D_HPP


#include <vikr/shader/spv/spv_texture_2d.hpp>


namespace vikr {


class SpvTexture3D : public SpvTexture2D {
public:

  vint32 Finalize() override;
  
  vint32 GetDepth() override { return m_depth; }

private:
  vint32 m_depth;
};
} // vikr
#endif // __VIKR_SPV_TEXTURE_3D_HPP