//
// Copyright (c) Mario Garcia. Under the MIT license.
//
#ifndef __VIKR_TIME_HPP
#define __VIKR_TIME_HPP

// OpenGL and Vulkan includes.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vikr_types.hpp"


namespace vikr {


// Takes the offset of the time it takes to render one frame after the other.
// Delta time is calculated how long it takes to render one frame, and solve the difference
// between that time and the time it took to render the last frame.
vreal32 GetDeltaTime();

// Takes the current time at the exact moment.
vreal32 GetTime();


namespace internals {


void CalculateDeltaTime();
} // internals
} // vikr
#endif // __VIKR_TIME_HPP