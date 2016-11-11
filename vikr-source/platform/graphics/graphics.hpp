//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_HPP
#define __VIKR_GRAPHICS_HPP

#include <platform/platform.hpp>

#include <platform/graphics/opengl.hpp>

#include <platform/graphics/vk.hpp>


namespace vikr {


/**
  Graphics Pipeline to implement.
*/
enum GraphicsPipeline {
  vikr_OPENGL,
  vikr_VULKAN
};
} // vikr
#endif // __VIKR_GRAPHICS_HPP