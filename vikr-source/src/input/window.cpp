//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/input/window.hpp>
#include <vikr/vikr.hpp>


namespace vikr {


Window *Window::m_mainWindow = nullptr;
const std::string Window::kAppName = "Vikr";


Window::Window(std::string name, vuint32 width, vuint32 height) 
  : m_width(width)
  , m_height(height)
  , application_name(name)
  , m_window(nullptr)
{
}


Window Window::CreateVikrWindow(vuint32 width, vuint32 height, std::string app_name) {
  Window win;
  win.m_window = VikrCreateGLFWwindow(width, height, app_name.c_str(), nullptr, nullptr);
  win.m_width = width;
  win.m_height = height;
  win.application_name = app_name;
  return std::move(win);
}


vbool Window::IsClosed() {
  if (m_window) {
    return glfwWindowShouldClose(m_window);
  }
  return false;
}


vvoid Window::Close() {
  glfwSetWindowShouldClose(m_window, GL_TRUE);
}


vvoid Window::SetMainWindow(Window *newWindow) {
  if (newWindow) {
    m_mainWindow = newWindow;
    VikrMakeContextCurrent(newWindow->m_window);
  }
  if(!GladLoaded()) {
    LoadGlad();
  }
}
} // vikr