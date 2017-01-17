//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TOOLS_STOPWATCH_HPP
#define __VIKR_TOOLS_STOPWATCH_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <array>
#include <chrono>


namespace vikr {


/**
  Quick implementation of a stopwatch.
*/
class Stopwatch {

  /**
    Time struct for the stopwatch.
  */
  struct Time {
    char                      title[32];
    std::chrono::milliseconds ms;
    std::chrono::microseconds us;
  };
public:
  
  
  static vvoid Start();

  static vvoid Stop();

  static vvoid Lap(const vchar *title);

  static vbool IsRunning() { return running; }

private:
  
  static vbool running;

  static std::array<Time, 10> m_stamps;
};
} // vikr
#endif // __VIKR_TOOLS_STOPWATCH_HPP