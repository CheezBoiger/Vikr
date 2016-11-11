//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VULKAN_HPP
#define __VIKR_VULKAN_HPP



#if defined (VIKR_VULKAN_ENABLED)
#include <vulkan/vulkan.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VIKR_VULKAN
#include <platform/vikr_api.hpp>
#include <platform/platform.hpp>



#endif // VIKR_VULKAN_ENABLED

/*

  Still need to read up on this.
*/
#endif // __VIKR_VULKAN_HPP