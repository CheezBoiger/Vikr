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
class GLSLShaderProgram;
class GL4PipelineState;


/**
  The OpenGL Resource Manager.
*/
class GLResourceManager : public ResourceManager {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GLResourceManager);
  GLResourceManager();

  Shader *CreateShader(std::string name, ShaderStage stage) override;
  Shader *GetShader(std::string name) override;
  vbool DestroyShader(std::string name) override;

  PipelineState *CreatePipelineState(std::string name) override;
  PipelineState *GetPipelineState(std::string name) override;
  vbool DestroyPipelineState(std::string name) override;

  Mesh *CreateMesh(std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> uvs,
    std::vector<vuint32> indices = std::vector<vuint32>(),
    std::vector<glm::vec3> tangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> bitangents = std::vector<glm::vec3>()) override;

  Mesh *CreateMesh(std::vector<Vertex> vertices,
    std::vector<vuint32> indices = std::vector<vuint32>()) override;

  Mesh *GetMesh(guid_t guid) override;
  vbool DestroyMesh(guid_t guid) override;

  Material *CreateMaterial(std::string mat_name) override;
  Material *GetMaterial(std::string name) override;
  vbool DestroyMaterial(std::string name) override;

  Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) override;
  Texture *GetTexture(std::string image_path) override;
  vbool DestroyTexture(std::string name) override;

  ShaderProgram *CreateShaderProgram() override;
  ShaderProgram *GetShaderProgram(guid_t id) override;
  vbool DestroyShaderProgram(guid_t id) override;
};


/**
  OpenGL Specific Resources.
*/
class GLResources : public Resources {
  static std::unordered_map<std::string, std::shared_ptr<GLSLShader> > shaders;

  /**
  Contains PtrToMesh data.
  */
  static std::map<guid_t, std::shared_ptr<Mesh> > meshes;

  /**
  Contains material data.
  */
  static std::map<std::string, std::shared_ptr<Material> > materials;
  static std::map<std::string, std::shared_ptr<GLTexture> > textures;

  static std::map<guid_t, std::shared_ptr<GLSLShaderProgram> > shader_programs;
  static std::map<std::string, std::shared_ptr<GL4PipelineState> > pipelinestates; 

  friend class GLResourceManager;
};
} // vikr
#endif // __VIKR_OPENGL_RESOURCES_HPP