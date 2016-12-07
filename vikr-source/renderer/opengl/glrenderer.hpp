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
class DebugCommand;
class GroupCommand;
class MaterialCommand;
class PrimitiveCommand;
class TransformCommand;
class LightCommand;
class GLRenderTarget;
class Mesh;


/**
  Renderer using OpenGL Graphics APIs.
*/
class GLRenderer : public Renderer {
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
  vint32 ExecuteDebugCommand(DebugCommand *cmd);
  vint32 ExecuteGroupCommand(GroupCommand *cmd);
  vint32 ExecuteMaterialCommand(MaterialCommand *cmd);
  vint32 ExecutePrimitiveCommand(PrimitiveCommand *cmd);
  vint32 ExecuteTransformCommand(TransformCommand *cmd);

private:

  Shader *current_shader    = nullptr;

  VIKR_DISALLOW_COPY_AND_ASSIGN(GLRenderer);

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP