//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_OPENGL_RESOURCES_HPP
#define __VIKR_OPENGL_RESOURCES_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/scene_node.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/shader/texture.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace vikr {


class GLSLShader;
class GLTexture;


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
    std::vector<vuint32> indices = std::vector<vuint32>(),
    std::vector<glm::vec3> tangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> bitangents = std::vector<glm::vec3>()) override;


  Mesh *CreateMesh(std::vector<Vertex> vertices,
    std::vector<vuint32> indices = std::vector<vuint32>()) override;

  Mesh *GetMesh(guid_t guid) override;

  Material *CreateMaterial(std::string mat_name) override;

  Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) override;
  Texture *GetTexture(std::string image_path) override;

  vint32 StoreShader(std::string shader_name,
    std::string vs,
    std::string fs,
    std::string include_path = ".",
    std::string gs = "") override;

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
  static std::map<guid_t, std::shared_ptr<Mesh> > meshes;

  /**
  Contains material data.
  */
  static std::map<std::string, std::shared_ptr<Material> > materials;
  static std::map<std::string, std::shared_ptr<GLTexture> > textures;

  friend class GLResourceManager;
};
} // vikr
#endif // __VIKR_OPENGL_RESOURCES_HPP