//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_WINDOW_HPP
#define __VIKR_WINDOW_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <string>


struct GLFWwindow;


namespace vikr {


using VikrWindow = GLFWwindow;


/**
  Window Screen for use as a Singleton, This is helpful for our situation as it allows us 
  to work with a global main window, or to work with multiple windows if need be. 

  Currently only supports one window at a time.
*/
class Window {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Window);
  static const std::string kAppName;
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Window);

  Window(std::string name = kAppName, vuint32 width = 0, vuint32 height = 0);
  /**
    Create a main window.
  */
  static Window CreateVikrWindow(vuint32 width, vuint32 height, std::string app_name = "Vikr");

  /**
    Get the Main window.
  */
  static Window *GetMainWindow() { return m_mainWindow; }

  /**
    Get the main window width.
  */
  vuint32 GetWidth() { return m_width; }

  /**
    Get the main window height. 
  */
  vuint32 GetHeight() { return m_height; }

  /**
    Get the main window application.
  */
  std::string GetApplicationName() { return application_name; }

  VikrWindow *GetWindow() { return m_window; }

  /**
    Set the Main window.
  */
  static vvoid SetMainWindow(Window *newWindow);

  /**
    Close the window.
  */
  vvoid Close();

  /**
    Check if the window is closed. 
  */
  vbool IsClosed();

private:

  /**
    Application name.
  */
  std::string application_name;
  /**
    The width of the Main window.
  */
  vuint32 m_width;

  /**
    The height of the Main window.
  */
  vuint32 m_height;


  /**
    Window.
  */
  VikrWindow *m_window;

  /**
    The Main window reference.
  */
  static Window *m_mainWindow;
};
} // vikr
#endif // __VIKR_WINDOW_HPP