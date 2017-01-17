//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_GRAPHICS_COMMAND_HPP
#define __VIKR_GL4_GRAPHICS_COMMAND_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>



namespace vikr {


class GL4RenderContext;


class GL4GraphicsCommand {
  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4GraphicsCommand);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4GraphicsCommand);
  GL4GraphicsCommand() { }
  virtual ~GL4GraphicsCommand() { }

  virtual vvoid Execute(GL4RenderContext *) = 0;
};
} // vikr
#endif // __VIKR_GL4_GRAPHICS_COMMAND_HPP