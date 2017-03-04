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
class GL4Texture;
class GLSLShaderProgram;
class GL4GraphicsPipelineState;
class GL4ComputePipelineState;


/**
  The OpenGL Resource Manager.
*/
class GLResourceManager : public ResourceManager {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GLResourceManager);
  GLResourceManager();

  /**
    Create a Shader object, provided a name and a shader stage.
  */
  Shader *CreateShader(std::string name, ShaderStage stage) override;
  
  /**
    Get the Shader object already stored in Resources, provided it's name given.
    @return the reference to the shader object. Nullptr if no shader was found by that
            name. 
  */
  Shader *GetShader(guid_t name) override;
  
  /**
    Destroy a Shader given its name.
    @return True if the shader was destroyed, false if no shader by the name provided, was 
    found.
  */
  vbool DestroyShader(guid_t name) override;

  /**
  */
  GraphicsPipelineState *CreateGraphicsPipelineState(std::string name) override;
  GraphicsPipelineState *GetGraphicsPipelineState(guid_t id) override;
  vbool DestroyGraphicsPipelineState(guid_t id) override;

  ComputePipelineState *CreateComputePipelineState(std::string name) override;
  ComputePipelineState *GetComputePipelineState(guid_t id) override;
  vbool DestroyComputePipelineState(guid_t id) override;

  Texture *CreateTexture(std::string name, TextureTarget target, 
    std::string filepath, vbool alpha) override;
  Texture *GetTexture(guid_t id) override;
  vbool DestroyTexture(guid_t id) override;

  ShaderProgram *CreateShaderProgram() override;
  ShaderProgram *GetShaderProgram(guid_t id) override;
  vbool DestroyShaderProgram(guid_t id) override;
};
} // vikr
#endif // __VIKR_OPENGL_RESOURCES_HPP