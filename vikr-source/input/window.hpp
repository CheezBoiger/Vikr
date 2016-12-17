//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_WINDOW_HPP
#define __VIKR_WINDOW_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

#include <string>


namespace vikr {


using VikrWindow = GLFWwindow;


/**
  Window Screen for use. Currently only supports one window at a time.
*/
class Window {
public:
  static vvoid CreateVikrWindow(vuint32 width, vuint32 height, std::string app_name = "Vikr");


  static VikrWindow *GetMainWindow() { return m_mainWindow; }
  static vuint32 GetWindowWidth() { return m_width; }
  static vuint32 GetWindowHeight() { return m_height; }
  static std::string GetApplicationName() { return application_name; }
  static vvoid Close(VikrWindow *window);

  static vbool IsClosed();

private:
  static std::string application_name;
  static vuint32 m_width;
  static vuint32 m_height;
  static VikrWindow *m_mainWindow;
};
} // vikr
#endif // __VIKR_WINDOW_HPP