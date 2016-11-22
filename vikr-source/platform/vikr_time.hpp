//
// Copyright (c) Mario Garcia. Under the MIT license.
//
#ifndef __VIKR_TIME_HPP
#define __VIKR_TIME_HPP

#include "vikr_types.hpp"


namespace vikr {
namespace internals {


static vreal32 last_time = static_cast<vreal32>(glfwGetTime());
static vreal32 last_frame = 0;
static vreal32 delta_time = 0;
static vreal32 fpms = 0;
static vuint32 fps = 0;
static vuint32 nb_frames = 0;

} // internals
// Takes the offset of the time it takes to render one frame after the other.
// Delta time is calculated how long it takes to render one frame, and solve the difference
// between that time and the time it took to render the last frame.
VIKR_FORCEINLINE vreal32 GetDeltaTime() { return internals::delta_time; }

// Takes the current time at the exact moment.
VIKR_FORCEINLINE vreal64 GetTime() { return glfwGetTime(); }


VIKR_FORCEINLINE vreal32 GetLastFrameTime() { return internals::last_frame; }

// Get Frames Per Millisecond ( this is useful for debugging performance.
VIKR_FORCEINLINE vreal32 GetFPMS() { return internals::fpms; }
// Get the Frames per Second ( This is to check a general view of performance ).
VIKR_FORCEINLINE vuint32 GetFPS() { return internals::fps; }


/**
  Calculates FPS.
*/
VIKR_FORCEINLINE void CalculateFPS() {
  internals::nb_frames += 1;
  if(GetTime() - internals::last_time >= 1.0f) {
    internals::fpms = static_cast<vreal32>(1000.0 / vreal64(internals::nb_frames));
    internals::fps = internals::nb_frames;
    internals::nb_frames = 0;
    internals::last_time += 1.0f;
  }
}


/**
  Calculates the Delta Time (the difference between the time it takes to render current 
  frame and the time it takes to render the last frame).
*/
VIKR_FORCEINLINE void CalculateDeltaTime() {
  vreal32 current_frame = static_cast<vreal32>(vikr::GetTime());
  internals::delta_time = current_frame - internals::last_frame;
  internals::last_frame = current_frame;
  CalculateFPS();
}
} // vikr
#endif // __VIKR_TIME_HPP