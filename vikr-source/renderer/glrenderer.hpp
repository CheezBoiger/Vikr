//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLRENDERER_HPP
#define __VIKR_GLRENDERER_HPP


#include <renderer/irenderer.hpp>
#include <renderer/render_queue.hpp>



namespace vikr {



class Camera;


/**
  Renderer using OpenGL Graphics APIs.
*/
class GLRenderer : public IRenderer {
public:
  GLRenderer();
  ~GLRenderer();


  Camera *GetCamera() { return current_camera; }
  vvoid SetCamera(Camera *camera) { current_camera = camera; }
  /**
    Swaps current camera with the camera specified.
  */
  vvoid SwapCameras(Camera *camera) { std::swap(current_camera, camera); }

  vint32 Init() override;
  vvoid PushBack(RenderCommand *command) override;
  vvoid Sort() override;
  vvoid Render() override;
private:


  RenderQueue m_command_list;
  /**
    Current camera that we render through.
  */
  Camera *current_camera;

  VIKR_DISALLOW_COPY_AND_ASSIGN(GLRenderer);

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP