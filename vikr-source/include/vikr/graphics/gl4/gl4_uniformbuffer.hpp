//
// Copyright (c) Mario Garcia, Under the MIT license.
//
#ifndef __VIKR_GL4_UNIFORMBUFFER_HPP
#define __VIKR_GL4_UNIFORMBUFFER_HPP


#include <vikr/graphics/uniformbuffer.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>


namespace vikr {


class GL4Uniformbuffer : public Uniformbuffer {
public:

  GL4Uniformbuffer();

  vvoid Generate(vuint32 bytes) override;

  vvoid Bind() override;
  vvoid Unbind() override;

  

private:

};
} // vikr
#endif // __VIKR_GL4_UNIFORMBUFFER_HPP