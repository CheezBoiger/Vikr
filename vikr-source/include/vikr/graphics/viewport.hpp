//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VIEWPORT_HPP
#define __VIKR_VIEWPORT_HPP

#include <vikr/platform/vikr_types.hpp>

namespace vikr {


#define VIKR_VIEWPORT_INIT(x, y, width, height) { x, y, width, height }

/**
  Viewport struct defines the view screen of the camera, and references
  the window's size;
*/
struct Viewport {
  /**
    Starting pixel width.
  */
  vuint32 win_x;
  /**
    Starting pixel height. 
  */
  vuint32 win_y;
  /**
    Max window width. 
  */
  vuint32 win_width;
  /**
    Max window height.
  */
  vuint32 win_height;
};

} // vikr
#endif // __VIKR_VIEWPORT_HPP