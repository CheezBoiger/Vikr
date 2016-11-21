//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLRENDERER_HPP
#define __VIKR_GLRENDERER_HPP


#include <renderer/renderer.hpp>
#include <renderer/render_queue.hpp>
#include <renderer/blendmode.hpp>
#include <renderer/depthmode.hpp>
#include <renderer/cullmode.hpp>


namespace vikr {



class Camera;
class MeshCommand;


/**
  Renderer using OpenGL Graphics APIs.
*/
class GLRenderer : public Renderer {
  static GLenum GetDepthFunct(DepthFunc funct);
  static GLenum GetBlendFunct(BlendFunc blend);
  static GLenum GetFrontFace(FrontFace face);
  static GLenum GetCullMode(CullFace mode);
public:
  GLRenderer();
  ~GLRenderer() { }


  vint32 Init() override;
  vvoid Render() override;

  vint32 ExecuteMeshCommand(MeshCommand *cmd);

private:

  VIKR_DISALLOW_COPY_AND_ASSIGN(GLRenderer);

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP