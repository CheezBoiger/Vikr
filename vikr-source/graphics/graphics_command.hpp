//
// Copyright(c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_COMMAND_HPP
#define __VIKR_GRAPHICS_COMMAND_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

#include <functional>


namespace vikr {


using FunctionCommand = std::function<vvoid()>;


class RenderContext;


/**
  Graphics command for the CommandBuffer to fill with.
*/
class GraphicsCommand {
public:
  

  virtual vvoid Execute(RenderContext *context) = 0;

private:

  FunctionCommand func;
};
} // vikr
#endif // __VIKR_GRAPHICS_COMMAND_HPP