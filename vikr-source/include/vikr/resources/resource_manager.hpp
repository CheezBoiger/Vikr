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
class PipelineState;
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
  ResourceManager(GraphicsPipeline pipe = vikr_PIPELINE_OPENGL);

  virtual ~ResourceManager() { }

  /**
    Create a shader, and store it into Resources, the id of the shader will 
    be returned. Resources takes care of this.
  */
  virtual Shader *CreateShader(std::string name, ShaderStage stage) = 0;
  virtual Shader *GetShader(guid_t id) = 0;
  virtual vbool DestroyShader(guid_t id) = 0;

  virtual PipelineState *CreatePipelineState(std::string name) = 0;
  virtual PipelineState *GetPipelineState(guid_t id) = 0;
  virtual vbool DestroyPipelineState(guid_t id) = 0;


  virtual ShaderProgram *CreateShaderProgram() = 0;
  virtual ShaderProgram *GetShaderProgram(guid_t id) = 0;
  virtual vbool DestroyShaderProgram(guid_t id) = 0;
  
  /**
    Creates the mesh object that is handled by the ResourceManager.
  */
  Mesh *CreateMesh(std::vector<glm::vec3> &positions,
    std::vector<glm::vec3> &normals,
    std::vector<glm::vec2> &uvs,
    std::vector<vuint32> &indices = std::vector<vuint32>(),
    std::vector<glm::vec3> &tangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> &bitangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> &colors = std::vector<glm::vec3>());
  
  /**
    Creates the mesh object, that is handled by the ResourceManager.
  */
  Mesh *CreateMesh(std::vector<Vertex> &vertices,
    std::vector<vuint32> &indices = std::vector<vuint32>());
  Mesh *GetMesh(guid_t guid);
  vbool DestroyMesh(guid_t guid);

  virtual Texture *CreateTexture(std::string name, TextureTarget target, 
    std::string filepath, vbool alpha) = 0;
  virtual Texture *GetTexture(guid_t id) = 0;
  virtual vbool DestroyTexture(guid_t id) = 0;

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


  GraphicsPipeline GetGraphicsPipeline() { return pipeline; }

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