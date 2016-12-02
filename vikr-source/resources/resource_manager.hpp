//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RESOURCES_HPP
#define __VIKR_RESOURCES_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

namespace vikr {


class Shader;
class Mesh;
class Material;
class SceneNode;
class SceneComponent;


/**
  Resource Manager handles Resources for the User to use.

  This includes handling Materials, Textures, Shaders, Meshes, and possibly
  SceneNodes.
*/
class ResourceManager {
public:
  ResourceManager(GraphicsPipeline pipe = vikr_OPENGL);

  virtual ~ResourceManager() { }

  virtual vint32 StoreShader(std::string name, Shader *shader) = 0;
  virtual Shader *GetShader(std::string name) = 0;
  virtual Mesh *CreateMesh(std::vector<glm::vec3> positions,
                           std::vector<glm::vec3> normals,
                           std::vector<glm::vec2> uvs,
                           std::vector<vuint32> indices = std::vector<vuint32>()) = 0;

  virtual Material *CreateMaterial() = 0;

  /**
    Much involves the interface design of ResourceManager, but this is common.
  */
  SceneNode *CreateSceneNode();

  static ResourceManager *GetResourceManager() { return resource_manager.get(); }
  static vvoid SetResourceManager(ResourceManager *r) { resource_manager.reset(r); }

private:
  /**
    Graphics pipeline of the ResourceManager.
  */
  GraphicsPipeline pipeline;
  /**
    Current ResourceManager.
  */
  static std::unique_ptr<ResourceManager> resource_manager;

};


/**
  Resources
*/
class Resources {
protected:

  /**
    The resources of scenenode and scenecomponents.
  */
  static std::unordered_map<guid_t, std::shared_ptr<SceneNode> > scene_nodes;
  static std::unordered_map<guid_t, std::shared_ptr<SceneComponent> > scene_components;

  friend class ResourceManager;
};
} // vikr
#endif // __VIKR_RESOURCES_HPP