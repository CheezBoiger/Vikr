//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_IRENDERER_HPP
#define __VIKR_IRENDERER_HPP

#include <platform/vikr_types.hpp>
#include <renderer/render_command.hpp>


namespace vikr {


// Interface Renderer
//
class IRenderer {
public:
  IRenderer() { }
  virtual ~IRenderer() { }

  virtual vvoid PushBack(RenderCommand *command) = 0;
  virtual vvoid Sort() = 0;
  
  /**
    Should render the frame. 
   */
  virtual vvoid Render() = 0;
};
} // vikr
#endif // __VIKR_IRENDERER_HPP