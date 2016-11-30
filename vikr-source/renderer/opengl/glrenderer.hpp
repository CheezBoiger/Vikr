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
  vint32 StoreShader(std::string shader_name, 
                     std::string vs, 
                     std::string fs, 
                     std::string include_path = ".") override;

  Shader *GetShader(std::string shader_name) override;

  Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) override;
  /**
    Executes the following MeshCommand. This is where we render meshes.
  */
  vint32 ExecuteMeshCommand(MeshCommand *cmd);

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