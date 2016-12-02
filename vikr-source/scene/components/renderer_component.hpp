//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDERER_COMPONENT_HPP
#define __VIKR_RENDERER_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <shader/material.hpp>
#include <shader/texture.hpp>
#include <vector>

namespace vikr {


/**
  Renderer Component is the component that is used to determine the renderer type
  for the MeshComponent (Provided that the SceneNode contains a mesh to work with.
*/
class RendererComponent : public SceneComponent {
public:
  /**
    RendererComponent stuff.
  */
  RendererComponent();

  vvoid Update() override;

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

}; 
} // vikr
#endif // __VIKR_RENDERER_COMPONENT_HPP