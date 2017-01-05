//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_IRENDERER_HPP
#define __VIKR_IRENDERER_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>


namespace vikr {


class Light;
class RenderCommand;
class RenderTarget;
class SceneNode;
class RenderDevice;
class ICamera;

/**
  Interface Renderer for use with the abstract renderer.
*/
class IRenderer {
public:
  IRenderer() { }
  virtual ~IRenderer() { }

  virtual vvoid PushBack(RenderCommand *command) = 0;
  virtual vvoid PushBack(SceneNode *obj) = 0;
  virtual vvoid PushBackDeferred(RenderCommand *command) = 0;

  virtual vvoid Sort() = 0;
  virtual vint32 Init(RenderDevice *device) = 0;

  virtual ICamera *GetCamera() = 0;
  virtual vvoid SetCamera(ICamera *camera) = 0;

  /**
    Should render the frame. 
   */
  virtual vvoid Render() = 0;

  /**
    Present the Frame.
  */
  virtual vvoid Present() = 0;
};
} // vikr
#endif // __VIKR_IRENDERER_HPP