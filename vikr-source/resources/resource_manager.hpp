//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RESOURCES_HPP
#define __VIKR_RESOURCES_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace vikr {


class Shader;
class Mesh;
class Material;


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

  static ResourceManager *GetResourceManager() { return resources.get(); }
  static vvoid SetResourceManager(ResourceManager *r) { resources.reset(r); }


private:

  GraphicsPipeline pipeline;

  static std::unique_ptr<ResourceManager> resources;
};
} // vikr
#endif // __VIKR_RESOURCES_HPP