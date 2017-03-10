//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RESOURCES_HPP
#define __VIKR_RESOURCES_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <vikr/scene/components/scene_component.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/mesh/imesh.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

namespace vikr {


class Shader;
class ShaderProgram;
class Mesh;
class GraphicsPipelineState;
class ComputePipelineState;
class Material;
class SceneNode;


/**
  Resource Manager handles Resources for the User to use. Create materials, but 
  handles them for the user.

  This includes handling Materials, Textures, Shaders, Meshes, and possibly
  SceneNodes.
*/
class ResourceManager {
public:
  ResourceManager();

  ~ResourceManager() { }
  
  /**
    Creates the mesh object that is handled by the ResourceManager.
  */
  Mesh *CreateMesh();
  Mesh *GetMesh(guid_t guid);
  vbool DestroyMesh(guid_t guid);

  /**
    Much involves the interface design of ResourceManager, but this is common.
  */
  SceneNode *CreateSceneNode();

  SceneNode *GetSceneNode(guid_t guid);

  /**
    Destroys SceneNode, along with a choice of whether or not you wish to 
    destroy the entire subtree heirarchy.
  */
  vbool DestroySceneNode(guid_t guid, vbool destroy_subtree);


  Material *CreateMaterial(std::string mat_name);
  Material *GetMaterial(std::string name);
  vbool DestroyMaterial(std::string name);
};




/**
  Resources
*/
class Resources {
protected:

  /**
    The resources of scenenode and scenecomponents.
  */
  static std::unordered_map<guid_t, std::unique_ptr<SceneNode> > scene_nodes;
  static std::map<std::string, std::shared_ptr<Material> > materials;

  /**
    Contains PtrToMesh data.
  */
  static std::map<guid_t, std::unique_ptr<Mesh> > meshes;

  friend class ResourceManager;
};
} // vikr
#endif // __VIKR_RESOURCES_HPP