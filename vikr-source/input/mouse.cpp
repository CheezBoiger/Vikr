//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <input/mouse.hpp>
#include <platform/vikr_time.hpp>
#include <renderer/renderer.hpp>
#include <scene/camera.hpp>


namespace vikr {


vvoid Mouse::DefaultMouseCallback(VikrWindow *window, vreal64 xpos, vreal64 ypos)
{
  if (firstMouse)
  {
    lastXPos = xpos;
    lastYPos = ypos;
    firstMouse = false;
  }

  vreal32 xoffset = static_cast<vreal32>(xpos - lastXPos);
  vreal32 yoffset = static_cast<vreal32>(lastYPos - ypos);

  lastXPos = xpos;
  lastYPos = ypos;
  IRenderer *renderer = Renderer::GetRenderer();
  if (renderer) {
    ICamera *camera = renderer->GetCamera();
    if (camera) {
      camera->Look(xoffset, yoffset, GetDeltaTime());
    }
  }
}


MouseCallback Mouse::callback;
Mouse::Mode Mouse::mode = Mouse::Mode::MOUSE_CURSOR_NORMAL;
vreal64 Mouse::lastXPos = 0;
vreal64 Mouse::lastYPos = 0;
vbool Mouse::firstMouse = true;


vint32 Mouse::RegisterMouseCallback(MouseCallback callback) {
  Mouse::callback = callback;
  glfwSetCursorPosCallback(Window::GetMainWindow(), Mouse::callback);
  lastXPos = static_cast<vreal64>(Window::GetWindowWidth());
  lastYPos = static_cast<vreal64>(Window::GetWindowHeight());
  firstMouse = true;
  return 1;
}


vint32 Mouse::UnRegisterMoustCallback() {
  return 0;
}


MouseCallback Mouse::GetMouseCallback() {
  return callback;
}


vvoid Mouse::SetMouseMode(Mode mode) {
  Mouse::mode = mode;
  glfwSetInputMode(Window::GetMainWindow(), GLFW_CURSOR, mode);
}
} // vikr
