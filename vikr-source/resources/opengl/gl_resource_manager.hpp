//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_OPENGL_RESOURCES_HPP
#define __VIKR_OPENGL_RESOURCES_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/scene_node.hpp>
#include <resources/resource_manager.hpp>
#include <mesh/opengl/glmesh.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace vikr {


class GLSLShader;


/**
  The OpenGL Resource Manager.
*/
class GLResourceManager : public ResourceManager {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GLResourceManager);
  GLResourceManager();

  vint32 StoreShader(std::string name, Shader *shader) override;
  Shader *GetShader(std::string name) override;

  Mesh *CreateMesh(std::vector<glm::vec3> positions,
                   std::vector<glm::vec3> normals,
                   std::vector<glm::vec2> uvs,
                   std::vector<vuint32> indices = std::vector<vuint32>()) override;

  Material *CreateMaterial() override;

};


/**
  OpenGL Specific Resources.
*/
class GLResources : public Resources {
  static std::unordered_map<std::string,
    std::pair<std::string, std::unique_ptr<GLSLShader> > > shaders;

  /**
  Contains PtrToMesh data.
  */
  static std::vector<std::shared_ptr<GLMesh> > meshes;

  /**
  Contains material data.
  */
  static std::vector<std::shared_ptr<Material> > materials;

  friend class GLResourceManager;
};
} // vikr
#endif // __VIKR_OPENGL_RESOURCES_HPP