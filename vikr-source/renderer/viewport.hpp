//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VIEWPORT_HPP
#define __VIKR_VIEWPORT_HPP

#include <platform/vikr_types.hpp>

namespace vikr {

/**
  Viewport struct defines the view screen of the camera, and references
  the window's size;
*/
struct Viewport {
  vint32 viewport_x;
  vint32 viewport_y;
  vint32 win_width;
  vint32 win_height;
};

} // vikr
#endif // __VIKR_VIEWPORT_HPP