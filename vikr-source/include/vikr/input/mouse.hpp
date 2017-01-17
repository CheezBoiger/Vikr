//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MOUSE_HPP
#define __VIKR_MOUSE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/input/window.hpp>
#include <unordered_map>


namespace vikr {


using MouseCallback = GLFWcursorposfun;
/**
  Mouse handle.
*/
class Mouse {
public:

  enum Mode {
    MOUSE_CURSOR_NORMAL = GLFW_CURSOR_NORMAL,
    MOUSE_CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
    MOUSE_CURSOR_DISABLED = GLFW_CURSOR_DISABLED
  };

  static vint32 RegisterMouseCallback(MouseCallback callback);
  static vint32 UnRegisterMoustCallback();

  static MouseCallback GetMouseCallback();

  static vvoid SetMouseMode(Mode mode);

  static vvoid DefaultMouseCallback(VikrWindow *window, vreal64 xpos, vreal64 ypos);


  static vreal64 lastXPos;
  static vreal64 lastYPos;
  static vbool firstMouse;

private:

  static Mode mode;
  static MouseCallback callback;
};
} // vikr
#endif // __VIKR_MOUSE_HPP