//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <input/window.hpp>
#include <vikr.hpp>


namespace vikr {


std::string Window::application_name = "Vikr";
vuint32 Window::m_height = 0;
vuint32 Window::m_width = 0;
VikrWindow *Window::m_mainWindow = nullptr;


vvoid Window::CreateVikrWindow(vuint32 width, vuint32 height, std::string app_name) {
  m_mainWindow = VikrCreateGLFWwindow(width, height, app_name.c_str(), nullptr, nullptr);
  VikrMakeContextCurrent(m_mainWindow);
  m_width = width;
  m_height = height;
  application_name = app_name;
  if (!GladLoaded()) {
    LoadGlad();
  }
}


vbool Window::IsClosed() {
  if (m_mainWindow) {
    return glfwWindowShouldClose(m_mainWindow);
  }
  return false;
}


vvoid Window::Close(VikrWindow *window) {
  glfwSetWindowShouldClose(window, GL_TRUE);
}
} // vikr