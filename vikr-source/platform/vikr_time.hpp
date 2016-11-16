//
// Copyright (c) Mario Garcia. Under the MIT license.
//
#ifndef __VIKR_TIME_HPP
#define __VIKR_TIME_HPP

#include "vikr_types.hpp"


namespace vikr {
namespace internals {


static vreal32 last_frame = 0;
static vreal32 delta_time = 0;

} // internals
// Takes the offset of the time it takes to render one frame after the other.
// Delta time is calculated how long it takes to render one frame, and solve the difference
// between that time and the time it took to render the last frame.
VIKR_FORCEINLINE vreal32 GetDeltaTime() { return internals::delta_time; }

// Takes the current time at the exact moment.
VIKR_FORCEINLINE vreal64 GetTime() { return glfwGetTime(); }


VIKR_FORCEINLINE vreal32 GetLastFrameTime() { return internals::last_frame; }


/**
  Calculates the Delta Time (the difference between the time it takes to render current 
  frame and the time it takes to render the last frame).
*/
VIKR_FORCEINLINE void CalculateDeltaTime() {
  vreal32 current_frame = static_cast<vreal32>(vikr::GetTime());
  internals::delta_time = current_frame - internals::last_frame;
  internals::last_frame = current_frame;
}
} // vikr
#endif // __VIKR_TIME_HPP