//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RESOURCES_HPP
#define __VIKR_RESOURCES_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <vikr/scene/components/scene_component.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/mesh/imesh.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

namespace vikr {


class Shader;
class Mesh;
class Material;
class SceneNode;


/**
  Resource Manager handles Resources for the User to use.

  This includes handling Materials, Textures, Shaders, Meshes, and possibly
  SceneNodes.
*/
class ResourceManager {
public:
  ResourceManager(GraphicsPipeline pipe = vikr_PIPELINE_OPENGL);

  virtual ~ResourceManager() { }

  virtual vint32 StoreShader(std::string name, Shader *shader) = 0;
  virtual Shader *GetShader(std::string name) = 0;
  
  /**
    Creates the mesh object that is handled by the ResourceManager.
  */
  virtual Mesh *CreateMesh(std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> uvs,
    std::vector<vuint32> indices = std::vector<vuint32>(),
    std::vector<glm::vec3> tangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> bitangents = std::vector<glm::vec3>()) = 0;
  
  /**
    Creates the mesh object, that is handled by the ResourceManager.
  */
  virtual Mesh *CreateMesh(std::vector<Vertex> vertices,
    std::vector<vuint32> indices = std::vector<vuint32>()) = 0;
  virtual Mesh *GetMesh(guid_t guid) = 0;

  virtual Material *CreateMaterial(std::string mat_name) = 0;

  virtual Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) = 0;
  virtual Texture *GetTexture(std::string image_path) = 0;

  virtual vint32 StoreShader(std::string shader_name,
                             std::string vs,
                             std::string fs,
                             std::string include_searchpath = ".",
                             std::string gs = "") = 0;

  /**
    Much involves the interface design of ResourceManager, but this is common.
  */
  SceneNode *CreateSceneNode();

  SceneNode *GetSceneNode(guid_t guid);

  /**
    Destroys SceneNode, along with a choice of whether or not you wish to 
    destroy the entire subtree heirarchy.
  */
  vint32 DestroySceneNode(guid_t guid, vbool destroy_subtree);

private:
  /**
    Graphics pipeline of the ResourceManager.
  */
  GraphicsPipeline pipeline;

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

  friend class ResourceManager;
};
} // vikr
#endif // __VIKR_RESOURCES_HPP