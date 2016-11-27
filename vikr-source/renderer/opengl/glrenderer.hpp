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
                     std::string include_path) override;

  Shader *GetShader(std::string shader_name) override;

  Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) override;

  vint32 ExecuteMeshCommand(MeshCommand *cmd);

private:

  VIKR_DISALLOW_COPY_AND_ASSIGN(GLRenderer);

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP