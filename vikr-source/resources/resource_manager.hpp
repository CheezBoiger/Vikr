//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RESOURCES_HPP
#define __VIKR_RESOURCES_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>
#include <scene/components/scene_component.hpp>
#include <shader/texture.hpp>
#include <mesh/imesh.hpp>
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
    std::vector<vuint32> indices = std::vector<vuint32>()) = 0;
  
  /**
    Creates the mesh object, that is handled by the ResourceManager.
  */
  virtual Mesh *CreateMesh(std::vector<Vertex> vertices,
    std::vector<vuint32> indices = std::vector<vuint32>()) = 0;

  virtual Material *CreateMaterial() = 0;

  virtual Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) = 0;

  virtual vint32 StoreShader(std::string shader_name,
                             std::string vs,
                             std::string fs,
                             std::string include_searchpath = ".") = 0;

  /**
    Much involves the interface design of ResourceManager, but this is common.
  */
  SceneNode *CreateSceneNode();

  SceneNode *GetSceneNode(guid_t guid);

  /**
    Destroys SceneNode, It's children remain intact though, so be sure to wipe them out as well.
  */
  vint32 DestroySceneNode(guid_t guid);

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