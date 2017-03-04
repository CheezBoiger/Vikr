//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_IRENDERER_HPP
#define __VIKR_IRENDERER_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <glm/glm.hpp>


namespace vikr {


class Light;
class RenderCommand;
class RenderTarget;
class SceneNode;
class RenderDevice;
class ResourceManager;
class ICamera;

/**
  Interface Renderer for use with the abstract renderer.
*/
class IRenderer {
public:
  IRenderer() { }
  virtual ~IRenderer() { }

  /**
    Pushback a RenderCommand into the render queue of the renderer.
  */
  virtual vvoid PushBack(RenderCommand *command) = 0;
  
  /**
    Pushback a SceneNode int othe render queue of the renderer.
  */
  virtual vvoid PushBack(SceneNode *obj) = 0;
  
  /**
    Pushback a RenderCommand into the deferred render queue of the renderer.
  */
  virtual vvoid PushBackDeferred(RenderCommand *command) = 0;

  /**
    Sort the Rendercommands that were pushed into the render queue of this renderer.
  */
  virtual vvoid Sort() = 0;

  /**
    Initialize the Renderer with the given RenderDevice.
  */
  virtual vint32 Init(RenderDevice *device, ResourceManager *mgr) = 0;

  /**
    Get the currently used camera from the renderer.
  */
  virtual ICamera *GetCamera() = 0;

  /**
    Set the current camera for the renderer.
  */
  virtual vvoid SetCamera(ICamera *camera) = 0;

  /**
    Cleanup this Renderer's resources.
  */
  virtual vint32 CleanupResources() = 0;

  /**
    Get the RenderDevice being used by this Renderer.
  */
  virtual RenderDevice *GetDevice() = 0;

  /**
    Set the Clear Color.
  */
  virtual vvoid SetClearColor(glm::vec4 cc) = 0;

  /**
    Get the Clear Color.
  */
  virtual glm::vec4 GetClearColor() = 0;

  /**
    Check if this renderer is in the middle of rendering.
  */
  virtual vbool IsRendering() = 0;

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