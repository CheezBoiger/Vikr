//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <input/keyboard.hpp>
#include <input/window.hpp>

namespace vikr {


// Is called whenever a key is pressed/released via GLFW
vvoid Keyboard::DefaultKeyCallback(VikrWindow *window, vint32 key, 
  vint32 scancode, vint32 action, vint32 mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    Window::Close(Window::GetMainWindow());

    if(action == GLFW_PRESS) {
      key_map[(Key )key] = Mode::KEY_PRESS;
    } else if(action == GLFW_REPEAT) {
      key_map[(Key )key] = Mode::KEY_REPEAT;
    } else if(action == GLFW_RELEASE) {
      key_map[(Key )key] = Mode::KEY_RELEASE;
    }
}


KeyboardCallback Keyboard::callback;
vbool Keyboard::enable = false;
std::unordered_map<Keyboard::Key, Keyboard::Mode> Keyboard::key_map;


vint32 Keyboard::RegisterKeyboardCallback(KeyboardCallback callback) {
  Keyboard::callback = callback;
  glfwSetKeyCallback(Window::GetMainWindow(), Keyboard::callback);
  return 1;
}


vint32 Keyboard::UnRegisterKeyboardCallback() {
  return 0;
}


vbool Keyboard::SetEnable(vbool enable) {
  Keyboard::enable = enable;
  if (enable) {  }
  return false;
}
} // vikr