//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLRENDERER_HPP
#define __VIKR_GLRENDERER_HPP


#include <renderer/irenderer.hpp>
#include <renderer/render_queue.hpp>



namespace vikr {


/**
  Renderer using OpenGL Graphics APIs.
*/
class GLRenderer : public IRenderer {
public:
  GLRenderer();
  ~GLRenderer();

  vint32 Init() override;
  vvoid PushBack(RenderCommand *command) override;
  vvoid Sort() override;
  vvoid Render() override;
private:


  RenderQueue m_command_list;

  VIKR_DISALLOW_COPY_AND_ASSIGN(GLRenderer);

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP