//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/platform/vikr_time.hpp>


#include <vikr/graphics/graphics.hpp>


namespace vikr {


vreal64 VikrTime::last_time = glfwGetTime();
vreal64 VikrTime::last_frame = 0;
vreal64 VikrTime::delta_time = 0;
vreal64 VikrTime::fpms = 0;
vuint64 VikrTime::fps = 0;
vuint64 VikrTime::nb_frames = 0;


vreal64 GetTime() 
{
  return glfwGetTime();
}
} // vikr