//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERER_COMPONENT_HPP
#define __VIKR_RENDERER_COMPONENT_HPP


#include <vikr/scene/components/scene_component.hpp>
#include <vikr/renderer/command/material_command.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/shader/texture.hpp>
#include <vector>

namespace vikr {


/**
  Renderer Component is the component that is used to determine the renderer type
  for the MeshComponent (Provided that the SceneNode contains a mesh to work with.

  TODO(): We cannot let the material set the shader unless absolutely required!
*/
class RendererComponent : public SceneComponent {
public:
  /**
    RendererComponent stuff.
  */
  RendererComponent();

  vvoid Update() override;

  RenderCommand *GetCommand() override { return &cmd; }

  /**
  Material implementation.
  */
  Material *material;
  /**
    Setting textures. These can be in the form of 
    albedo, diffuse, ambient, specular, and what ever else.
  */
  std::vector<Texture *> textures;

private:

  MaterialCommand cmd;
}; 
} // vikr
#endif // __VIKR_RENDERER_COMPONENT_HPP