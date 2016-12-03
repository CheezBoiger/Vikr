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
#include <math/shape/quad.hpp>
#include <mesh/mesh.hpp>

namespace vikr {



class Camera;
class MeshCommand; 
class PrimitiveCommand;
class Mesh;


/**
  Renderer using OpenGL Graphics APIs.
*/
class GLRenderer : public Renderer {
  static GLenum GetDepthFunct(DepthFunc funct);
  static GLenum GetBlendFunct(BlendFunc blend);
  static GLenum GetCullFace(CullFace face);
  static GLenum GetFrontFace(FrontFace mode);
public:
  GLRenderer();
  ~GLRenderer() { }


  vint32 Init() override;
  vvoid Render() override;


  vvoid Draw(GLenum topology, vuint32 vertices, vuint32 start);
  /**
    Executes the following MeshCommand. This is where we render meshes.
  */
  vint32 ExecuteMeshCommand(MeshCommand *cmd);


  vint32 ExecutePrimitiveCommand(PrimitiveCommand *cmd);
  /**
    Sets the context of the OpenGL mesh in terms of whether or not 
    to disable/enable blending, depth, or culling
  */
  vvoid SetGLContext(Material *material);

private:

  VIKR_DISALLOW_COPY_AND_ASSIGN(GLRenderer);

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP