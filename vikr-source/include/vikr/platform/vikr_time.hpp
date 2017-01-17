//
// Copyright (c) Mario Garcia. Under the MIT license.
//
#ifndef __VIKR_TIME_HPP
#define __VIKR_TIME_HPP

#include "vikr_types.hpp"


namespace vikr {


/*
  Time struct.
*/
struct VikrTime {

  static vreal64 last_time;
  static vreal64 last_frame;
  static vreal64 delta_time;
  static vreal64 fpms;
  static vuint64 fps;
  static vuint64 nb_frames;
};
// Takes the offset of the time it takes to render one frame after the other.
// Delta time is calculated how long it takes to render one frame, and solve the difference
// between that time and the time it took to render the last frame.
VIKR_FORCEINLINE vreal64 GetDeltaTime() { return VikrTime::delta_time; }

// Takes the current time at the exact moment.
VIKR_FORCEINLINE vreal64 GetTime() { return glfwGetTime(); }


VIKR_FORCEINLINE vreal64 GetLastFrameTime() { return VikrTime::last_frame; }

// Get Frames Per Millisecond ( this is useful for debugging performance.
VIKR_FORCEINLINE vreal64 GetFPMS() { return VikrTime::fpms; }
// Get the Frames per Second ( This is to check a general view of performance ).
VIKR_FORCEINLINE vuint64 GetFPS() { return VikrTime::fps; }


/**
  Calculates FPS.
*/
VIKR_FORCEINLINE void CalculateFPS() {
  VikrTime::nb_frames += 1;
  if(GetTime() - VikrTime::last_time >= 1.0f) {
    VikrTime::fpms = (1000.0 / VikrTime::nb_frames);
    VikrTime::fps = VikrTime::nb_frames;
    VikrTime::nb_frames = 0;
    VikrTime::last_time += 1.0f;
  }
}


/**
  Calculates the Delta Time (the difference between the time it takes to render current 
  frame and the time it takes to render the last frame).
*/
VIKR_FORCEINLINE void CalculateDeltaTime() {
  vreal64 current_frame = vikr::GetTime();
  VikrTime::delta_time = current_frame - VikrTime::last_frame;
  VikrTime::last_frame = current_frame;
  CalculateFPS();
}
} // vikr
#endif // __VIKR_TIME_HPP