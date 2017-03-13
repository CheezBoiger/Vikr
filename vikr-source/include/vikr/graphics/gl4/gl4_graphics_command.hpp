//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_GRAPHICS_COMMAND_HPP
#define __VIKR_GL4_GRAPHICS_COMMAND_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>


#include <functional>


namespace vikr {


class GL4RenderContext;


using GL4GraphicsCommand = std::function<vvoid()>;
} // vikr
#endif // __VIKR_GL4_GRAPHICS_COMMAND_HPP